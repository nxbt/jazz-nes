#include "cpu.h"
#include "bus.h"
#include "ram.h"
#include "cartridge.h"
#include "nes.h"

#include <iostream>

int main() {
    Nes nes;

    nes.load_cartridge("test_roms/nestest.nes");

    uint16_t result, prev_result;
    while(true) {
        nes.cpu().tick();
    }

    return 0;
}