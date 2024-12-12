#include "model.h"

int numByte(int ind) {
    return ind % 8 != 0 || ind == 0 ? ind / 8 + 1 : ind / 8;
}

int numInByte(int column) {
    if (column < 8) {
        return column;
    }
    return column % 8 == 0 ? 0 : column % 8;
}

bool checkBit(unsigned char byte, int pos) {
    return static_cast<bool>((1 << (7 - pos)) & byte);
}

void setTrue(unsigned char &byte, int pos) {
    byte |= (1 << (7 - pos));
}

void setFalse(unsigned char &byte, int pos) {
    byte &= ~(1 << (7 - pos));
}

int normalize(int coord, int size) {
    int k = coord / size;
    k -= coord < (-1) * size ? 1 : 0;
    if (coord >= 0 || coord < (-1) * size) {
        coord -= k * size;
    } else {
        coord += size;
    }
    return coord;
}

Field::Field() {
    field_.resize(size_ * numByte(size_), 0);
}

Field::Field(std::vector<Point> coords) {
    field_.resize(size_ * numByte(size_), 0);
    for (auto& i: coords) {
        if (i.x < 0 || i.x >= size_ || i.y < 0 || i.y >= size_) {
            throw std::invalid_argument("Coordinates out of range");
        }
        int num_byte = i.x * numByte(size_) + numByte(i.y);
        int pos = numInByte(i.y);
        num_byte += i.y % 8 == 0 && i.y != 0 ? 0 : -1;
        if (checkBit(field_[num_byte], pos)) {
            throw std::invalid_argument("Coordinates repeate");
        } else {
            setTrue(field_[num_byte], pos);
        }
    }
}

int Field::getSize() const {
    return size_;
}

bool Field::getState(int row, int column) const {
    int num_byte = row * numByte(size_) + numByte(column);
    int pos = numInByte(column);
    num_byte += column % 8 == 0 && column != 0 ? 0 : -1;
    return checkBit(field_[num_byte], pos);
}

void Field::setState(int row, int column, bool value) {
    int num_byte = row * numByte(size_) + numByte(column);
    int pos = numInByte(column);
    num_byte += column % 8 == 0 && column != 0 ? 0 : -1;
    if (value) {
        setTrue(field_[num_byte], pos);
    } else {
        setFalse(field_[num_byte], pos);
    }
}

std::vector<bool> ruleToBool(const std::string &rule) {
    std::vector<bool> new_rule(9, false);
    for (const auto &i: rule) {
        new_rule[i - '0'] = true;
    }
    return std::move(new_rule);
}

int Field::neighbors(int row, int column) const {
    int count = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i != 0 || j != 0) {
                int n_row = normalize(row + i, size_);
                int n_column = normalize(column + j, size_);
                if (getState(n_row, n_column)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

std::vector<std::vector<bool>> Field::toVector() const {
    std::vector<std::vector<bool>> grid(size_, std::vector<bool>(size_, false));
    for (int row = 0; row < size_; ++row) {
        for (int column = 0; column < size_; ++column) {
            grid[row][column] = getState(row, column);
        }
    }
    return grid;
}

Game_model::Game_model(): Game_model(
        Default_name,
        Default_b_rule,
        Default_s_rule,
        Default_frame
) {}

Game_model::Game_model(
        const std::string& name,
        const std::string& brule,
        const std::string& srule,
        const std::vector<Point>& coords
):
        name_(name),
        b_rule_(ruleToBool(brule)),
        s_rule_(ruleToBool(srule)),
        field_1_(coords)
{};

const Field& Game_model::getField() const {
    return  field_1_;
}

const std::string& Game_model::getName() const {
    return name_;
}

int Game_model::getGlobIteration() const {
    return global_iteration_;
}

void Game_model::computeIteration() {
    for (int i = 0; i < field_1_.getSize(); ++i) {
        for (int j = 0; j < field_1_.getSize(); ++j) {
            field_2_.setState(i, j, false);
            int count_neigh = field_1_.neighbors(i, j);
            if (field_1_.getState(i, j) && s_rule_[count_neigh]) {
                field_2_.setState(i, j, true);
            } else if (!field_1_.getState(i, j) && b_rule_[count_neigh]) {
                field_2_.setState(i, j, true);
            }
        }
    }
    std::swap(field_1_, field_2_);
    ++global_iteration_;
}
