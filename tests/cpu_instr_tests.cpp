#include "cpu.h"
#include "bus.h"

#include <iostream>

class DummyBus : public Bus {

};

int main() {
    Bus bus = Bus();
    Cpu cpu = Cpu(bus);

    return 0;
}