#include <bus.h>
#include <cpu.h>

#include <iostream>
#include <fstream>

int main() {
    std::ifstream file;
    std::cout << file.exceptions() << "\n";
    file.exceptions(std::ios_base::failbit);
    try {
        file.open("fake.lol");
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        std::exit(EXIT_FAILURE);
    }

    return 0;
}