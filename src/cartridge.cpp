#include "cartridge.h"

#include "file_reader.h"
#include "rom.h"
#include "ram.h"
#include "bus.h"
#include "nes.h"
#include "cpu.h"

#include <iostream>

std::map<uint8_t, std::function<void(Cartridge&, Nes&)>> Cartridge::ines_mappers = {
    {0x00, setup_nrom},
};

Cartridge::Cartridge(std::string file_path): m_file_reader(file_path) {}

Cartridge::~Cartridge() {
    for(auto component : m_components) {
        delete component;
    }
}

void Cartridge::connect(Nes& nes) {
    ines_mappers[m_file_reader.get_mapper()](*this, nes);
}

void Cartridge::setup_nrom(Cartridge& cartridge, Nes& nes) {
    int prg_ram_size = 0x0800; // 2K
    int prg_rom_size = cartridge.m_file_reader.get_prg_rom_size();
    int chr_rom_size = cartridge.m_file_reader.get_chr_rom_size();

    Ram* prg_ram_ptr = new Ram(prg_ram_size);
    Rom* prg_rom_ptr = new Rom(prg_rom_size, cartridge.m_file_reader.get_prg_rom());
    Rom* chr_rom_ptr = new Rom(chr_rom_size, cartridge.m_file_reader.get_chr_rom());

    cartridge.m_components.push_back(prg_ram_ptr);
    cartridge.m_components.push_back(prg_rom_ptr);
    cartridge.m_components.push_back(chr_rom_ptr);

    // connect cartridge RAM and ROM to the cpu bus, mirroring as necessary
    for(int addr = 0x6000; addr < 0x7FFF; addr += prg_ram_size) {
        nes.cpu().bus().add_component(*prg_ram_ptr, addr);
    }

    for(int addr = 0x8000; addr < 0xFFFF; addr += prg_rom_size) {
        nes.cpu().bus().add_component(*prg_rom_ptr, addr);
    }
}
