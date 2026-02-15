#include <bus.h>
#include <cpu.h>

#include <iostream>

int main() {
    Bus bus;
    Cpu cpu(bus);

    return 0;
}