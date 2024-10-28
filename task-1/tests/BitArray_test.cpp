#include <gtest/gtest.h>
#include "../src/BitArray.h"

// Тесты конструктора по умолчанию
TEST(BitArrayTest, DefaultConstructor) {
BitArray ba;
EXPECT_EQ(ba.size(), 0);
EXPECT_TRUE(ba.empty());
}

// Тесты конструктора с параметрами
TEST(BitArrayTest, ParameterizedConstructor) {
BitArray ba(10, 5); // 10 битов, первые биты - 0b101
EXPECT_EQ(ba.size(), 10);
EXPECT_FALSE(ba.empty());
EXPECT_EQ(ba[0], true);
EXPECT_EQ(ba[1], false);
EXPECT_EQ(ba[2], true);
for (int i = 3; i < 10; ++i) {
EXPECT_EQ(ba[i], false);
}
}

// Тесты метода set и оператора []
TEST(BitArrayTest, SetAndAccess) {
BitArray ba(5);
ba.set(2);
EXPECT_EQ(ba[2], true);
ba[3] = true;
EXPECT_EQ(ba[3], true);
ba.set(4, false);
EXPECT_EQ(ba[4], false);
EXPECT_THROW(ba.set(-1), std::out_of_range);
EXPECT_THROW(ba.set(5), std::out_of_range);
}

// Тесты метода reset
TEST(BitArrayTest, Reset) {
BitArray ba(5);
ba.set();
ba.reset(2);
EXPECT_EQ(ba[2], false);
ba.reset();
for (int i = 0; i < ba.size(); ++i) {
EXPECT_EQ(ba[i], false);
}
}

// Тесты методов any, none, count
TEST(BitArrayTest, AnyNoneCount) {
BitArray ba(5);
EXPECT_FALSE(ba.any());
EXPECT_TRUE(ba.none());
EXPECT_EQ(ba.count(), 0);
ba.set(0);
EXPECT_TRUE(ba.any());
EXPECT_FALSE(ba.none());
EXPECT_EQ(ba.count(), 1);
ba.set(2);
EXPECT_EQ(ba.count(), 2);
}

// Тесты оператора ~
TEST(BitArrayTest, BitwiseNot) {
BitArray ba(5, 0b10101);
BitArray ba_not = ~ba;
EXPECT_EQ(ba_not.to_string(), "01010");
}

// Тесты операторов сравнения
TEST(BitArrayTest, ComparisonOperators) {
BitArray ba1(5, 0b10101);
BitArray ba2(5, 0b10101);
BitArray ba3(5, 0b01010);
EXPECT_TRUE(ba1 == ba2);
EXPECT_FALSE(ba1 != ba2);
EXPECT_TRUE(ba1 != ba3);
EXPECT_FALSE(ba1 == ba3);
EXPECT_FALSE(ba1 == BitArray(4, 0b1010));
}

// Тесты метода to_string
TEST(BitArrayTest, ToString) {
BitArray ba(8, 0b11001100);
EXPECT_EQ(ba.to_string(), "00110011");
}

// Тесты метода swap
TEST(BitArrayTest, Swap) {
BitArray ba1(5, 0b10101);
BitArray ba2(5, 0b01010);
ba1.swap(ba2);
EXPECT_EQ(ba1.to_string(), "01010");
EXPECT_EQ(ba2.to_string(), "10101");
}

// Тесты метода clear
TEST(BitArrayTest, Clear) {
BitArray ba(5, 0b10101);
ba.clear();
EXPECT_EQ(ba.size(), 0);
EXPECT_TRUE(ba.empty());
}

// Тесты исключений при неверных индексах
TEST(BitArrayTest, IndexOutOfBounds) {
BitArray ba(5);
EXPECT_THROW(ba.set(-1), std::out_of_range);
EXPECT_THROW(ba.set(5), std::out_of_range);
EXPECT_THROW(ba[-1], std::out_of_range);
EXPECT_THROW(ba[5], std::out_of_range);
}

