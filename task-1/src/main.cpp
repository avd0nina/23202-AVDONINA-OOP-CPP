#include <iostream>
#include "BitArray.h"

int main()
{
    // Создаем пустой BitArray
    BitArray ba1;
    std::cout << "ba1.empty(): " << ba1.empty() << std::endl;

    // Создаем BitArray с 10 битами, инициализируем первыми битами числа 5 (0b101)
    BitArray ba2(10, 5);
    std::cout << "ba2.size(): " << ba2.size() << std::endl;
    std::cout << "ba2.to_string(): " << ba2.to_string() << std::endl;

    // Устанавливаем биты по индексу
    ba2.set(3);
    ba2.set(7, true);
    ba2.set(0, false);
    std::cout << "After setting bits, ba2.to_string(): " << ba2.to_string() << std::endl;

    // Проверяем доступ по оператору []
    std::cout << "ba2[3]: " << ba2[3] << std::endl;
    ba2[3] = false;
    std::cout << "After ba2[3] = false, ba2.to_string(): " << ba2.to_string() << std::endl;

    // Используем битовые операции
    BitArray ba3(10, 3); // 0b11
    std::cout << "ba3.to_string(): " << ba3.to_string() << std::endl;

    BitArray ba_and = ba2 & ba3;
    std::cout << "ba2 & ba3: " << ba_and.to_string() << std::endl;

    BitArray ba_or = ba2 | ba3;
    std::cout << "ba2 | ba3: " << ba_or.to_string() << std::endl;

    BitArray ba_xor = ba2 ^ ba3;
    std::cout << "ba2 ^ ba3: " << ba_xor.to_string() << std::endl;

    // Проверяем сдвиги
    BitArray ba_shift_left = ba2 << 2;
    std::cout << "ba2 << 2: " << ba_shift_left.to_string() << std::endl;

    BitArray ba_shift_right = ba2 >> 2;
    std::cout << "ba2 >> 2: " << ba_shift_right.to_string() << std::endl;

    // Проверяем методы any(), none(), count()
    std::cout << "ba2.any(): " << ba2.any() << std::endl;
    std::cout << "ba2.none(): " << ba2.none() << std::endl;
    std::cout << "ba2.count(): " << ba2.count() << std::endl;

    // Инвертируем биты
    BitArray ba_not = ~ba2;
    std::cout << "~ba2: " << ba_not.to_string() << std::endl;

    // Используем push_back
    ba2.push_back(true);
    ba2.push_back(false);
    std::cout << "After push_back, ba2.size(): " << ba2.size() << std::endl;
    std::cout << "ba2.to_string(): " << ba2.to_string() << std::endl;

    // Используем resize
    ba2.resize(15, true);
    std::cout << "After resize to 15 with true, ba2.to_string(): " << ba2.to_string() << std::endl;

    // Используем clear
    ba2.clear();
    std::cout << "After clear, ba2.empty(): " << ba2.empty() << std::endl;

    return 0;
}