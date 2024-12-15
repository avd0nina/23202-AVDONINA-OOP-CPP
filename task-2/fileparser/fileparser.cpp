#include "fileparser.h"
#include <algorithm>

const std::string Digits = "012345678";

int parseNumber(const std::string& str) { // Преобразует строку в целое число, проверяя её корректность.
    if (str.empty() || (str[0] == '0' && str.size() > 1)) {
        throw std::invalid_argument("Ticks are zero or negative");
    }
    for (char c : str) {
        if (!isdigit(c) && c != '-') {
            throw std::invalid_argument("Number format is incorrect");
        }
    }
    return std::stoi(str);
}

std::string parseRule(const std::string& rule) { // Проверяет корректность строки правил rule и возвращает её.
    if (rule.empty() || !std::is_sorted(rule.begin(), rule.end())) {
        throw std::invalid_argument("Rule is incorrect");
    }
    for (char c : rule) {
        if (Digits.find(c) == std::string::npos) {
            throw std::invalid_argument("Rule contains invalid characters");
        }
    }
    return rule;
}

UniverseConfig FileParser::parseFile(const std::string& infile) { //  Разбирает файл конфигурации, возвращает объект UniverseConfig.
    UniverseConfig config; // Создаётся пустая структура для хранения результатов.
    std::ifstream file(infile); // Открывается файл на чтение.
    if (!file.is_open() || infile.size() < 5 || infile.substr(infile.size() - 4) != ".txt") {
        throw std::invalid_argument("Invalid input file");
    }

    std::string line;
    std::getline(file, line);
    if (line != "#Life 1.06") {
        throw std::invalid_argument("Invalid universe file format");
    }

    std::getline(file, line);
    if (line.size() < 3 || line.substr(0, 3) != "#N ") {
        throw std::invalid_argument("Invalid universe name format");
    }
    config.name = line.substr(3); // Имя сохраняется в поле config.name.

    std::getline(file, line);
    if (line.size() < 8 || line.substr(0, 4) != "#R B") {
        throw std::invalid_argument("Invalid rules format");
    }
    size_t slashPos = line.find('/');
    if (slashPos == std::string::npos || line[slashPos + 1] != 'S') {
        throw std::invalid_argument("Invalid rules format");
    }
    config.b_rule = parseRule(line.substr(4, slashPos - 4)); // Вызываются функции parseRule для валидации правил.
    config.s_rule = parseRule(line.substr(slashPos + 2));

    while (std::getline(file, line)) {
        size_t spacePos = line.find(' ');
        if (spacePos == std::string::npos) {
            throw std::invalid_argument("Invalid coordinates format");
        }
        int x = parseNumber(line.substr(0, spacePos)); // Числа x и y парсятся с помощью parseNumber
        int y = parseNumber(line.substr(spacePos + 1));
        config.coordinates.push_back({x, y}); // Координаты добавляются в config.coordinates
    }
    return config;
}