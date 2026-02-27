#include "nes.h"

#include "bus.h"
#include "cpu.h"
#include "cartridge.h"
#include "ram.h"

Nes::Nes() {
    m_cpu_ptr = new Cpu();

    m_onboard_ram_ptr = new Ram(0x0800);

    for(uint16_t addr = 0x0000; addr < 0x2000; addr += 0x0800) {
        cpu().bus().add_component(*m_onboard_ram_ptr, addr);
    }
}

Nes::~Nes() {
    delete m_cpu_ptr;

    delete m_cartridge_ptr;

    delete m_onboard_ram_ptr;
}

void Nes::load_cartridge(std::string file_path) {
    delete m_cartridge_ptr;
    m_cartridge_ptr = new Cartridge(file_path);
    m_cartridge_ptr->connect(*this);
}

Cpu& Nes::cpu() {
    return *m_cpu_ptr;
}
