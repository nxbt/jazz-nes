#include "bus.h"
#include "cpu.h"
#include "ram.h"
#include "cartridge.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>

int main() {
    Ram* onboard_ram_ptr = new Ram(0x0800);

    for(int addr = 0x0000; addr < 0x2000; addr += 0x0800) {
        Bus::instance().add_component(*onboard_ram_ptr, addr);
    }

    Cartridge cartridge("../nestest.nes");

    uint16_t result, prev_result;
    while(true) {
        Cpu::instance().tick();

        result = onboard_ram_ptr->read_data(0x02) | onboard_ram_ptr->read_data(0x03) << 4;
        if(result != prev_result) {
            std::cerr << "non-zero value 0x" << std::hex << result << "\n";
            prev_result = result;
        }
    }

    return 0;
}