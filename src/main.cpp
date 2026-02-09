#include <iostream>

int main() {
    bool a = true;
    std::cout << (int) (a << 7 | a << 6) << std::endl;
    return 0;
}