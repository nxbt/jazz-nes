#include "cpu.h"
#include "bus.h"
#include "ram.h"
#include "cartridge.h"
#include "nes.h"

#include <iostream>
#include <iomanip>

int main() {
    Nes nes;

    nes.load_cartridge("test_roms/nestest.nes");

    nes.cpu().debug_overwrite_pc(0xC000);

    while(true) {
        nes.cpu().tick();
    }

    uint8_t result_instrs_offical = nes.cpu().bus().read_data(0x02);
    uint8_t result_instrs_illegal = nes.cpu().bus().read_data(0x03);

    std::cerr << "RESULT: offical instruction byte: 0x" <<
        std::hex << std::setw(2) << std::setfill('0') << +result_instrs_offical << "\n";
    std::cerr << "RESULT: illegal instruction byte: 0x" <<
        std::hex << std::setw(2) << std::setfill('0') << +result_instrs_illegal << "\n";

    return 0;
}