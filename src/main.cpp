#include <iostream>

int main() {
    uint8_t a = 0xFF;
    uint8_t b = 0x01;
    uint16_t result = a + b;
    std::cout << (int) result << std::endl;
    return 0;
}