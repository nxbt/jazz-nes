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

    std::ofstream out("nestest.log", std::ios::binary);

    while(nes.cpu().debug_report_pc()) {
        out << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << nes.cpu().debug_report_pc() <<
            " A:" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +nes.cpu().debug_report_a() <<
            " X:" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +nes.cpu().debug_report_x() <<
            " Y:" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +nes.cpu().debug_report_y() <<
            " P:" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +nes.cpu().debug_report_ps() <<
            " SP:" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +nes.cpu().debug_report_sp() << '\n';
        
        nes.cpu().tick();
    }

    out.close();

    uint8_t result_instrs_offical = nes.cpu().bus().read_data(0x0002);
    uint8_t result_instrs_illegal = nes.cpu().bus().read_data(0x0003);

    std::cerr << "RESULT: offical instruction byte: 0x" <<
        std::hex << std::setw(2) << std::setfill('0') << +result_instrs_offical << "\n";
    std::cerr << "RESULT: illegal instruction byte: 0x" <<
        std::hex << std::setw(2) << std::setfill('0') << +result_instrs_illegal << "\n";

    if(result_instrs_offical || result_instrs_illegal) return -1;

    return 0;
}