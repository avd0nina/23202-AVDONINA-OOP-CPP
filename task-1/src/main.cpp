//#include <iostream>
//#include "BitArray.h"
//
//int main() {
//    BitArray ba1;
//    std::cout << "ba1.empty(): " << ba1.empty() << std::endl;
//
//    BitArray ba2(10, 5);
//    std::cout << "ba2.size(): " << ba2.size() << std::endl;
//    std::cout << "ba2.to_string(): " << ba2.to_string() << std::endl;
//
//    ba2.set(3);
//    ba2.set(7, true);
//    ba2.set(0, false);
//    std::cout << "After setting bits, ba2.to_string(): " << ba2.to_string() << std::endl;
//
//    std::cout << "ba2[3]: " << ba2[3] << std::endl;
//    ba2[3] = false;
//    std::cout << "After ba2[3] = false, ba2.to_string(): " << ba2.to_string() << std::endl;
//
//    BitArray ba3(10, 3); // 0b11
//    std::cout << "ba3.to_string(): " << ba3.to_string() << std::endl;
//
//    BitArray ba_and = ba2 & ba3;
//    std::cout << "ba2 & ba3: " << ba_and.to_string() << std::endl;
//
//    BitArray ba_or = ba2 | ba3;
//    std::cout << "ba2 | ba3: " << ba_or.to_string() << std::endl;
//
//    BitArray ba_xor = ba2 ^ ba3;
//    std::cout << "ba2 ^ ba3: " << ba_xor.to_string() << std::endl;
//
//    BitArray ba_shift_left = ba2 << 2;
//    std::cout << "ba2 << 2: " << ba_shift_left.to_string() << std::endl;
//
//    BitArray ba_shift_right = ba2 >> 2;
//    std::cout << "ba2 >> 2: " << ba_shift_right.to_string() << std::endl;
//
//    std::cout << "ba2.any(): " << ba2.any() << std::endl;
//    std::cout << "ba2.none(): " << ba2.none() << std::endl;
//    std::cout << "ba2.count(): " << ba2.count() << std::endl;
//
//    BitArray ba_not = ~ba2;
//    std::cout << "~ba2: " << ba_not.to_string() << std::endl;
//
//    ba2.push_back(true);
//    ba2.push_back(false);
//    std::cout << "After push_back, ba2.size(): " << ba2.size() << std::endl;
//    std::cout << "ba2.to_string(): " << ba2.to_string() << std::endl;
//
//    ba2.resize(15, true);
//    std::cout << "After resize to 15 with true, ba2.to_string(): " << ba2.to_string() << std::endl;
//
//    ba2.clear();
//    std::cout << "After clear, ba2.empty(): " << ba2.empty() << std::endl;
//    
//    
//
//    return 0;
//}
//

#include <iostream>
#include "BitArray.h"

int main() {
    BitArray obj(8, 0b1010); // 8 бит, начальное значение 0b1010
    BitArray result = 2 | obj; // 2 -> 0b0010
    std::cout << "Result of 2 | obj: " << result.to_string_bit() << std::endl;

    BitArray and_result = 3 & obj; // 3 -> 0b0011
    std::cout << "Result of 3 & obj: " << and_result.to_string_bit() << std::endl;

    BitArray xor_result = 7 ^ obj; // 7 -> 0b0111
    std::cout << "Result of 7 ^ obj: " << xor_result.to_string_bit() << std::endl;

    return 0;
}
