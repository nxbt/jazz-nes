#include "cartridge.h"

#include "file_reader.h"
#include "rom.h"
#include "ram.h"
#include "bus.h"

#include <iostream>

Cartridge::Cartridge(std::string file_path): m_file_reader(file_path) {
    // FileReader file_reader(file_path);

    // m_prg_rom_size = file_reader.get_prg_rom_size();
    // m_prg_ram_size = file_reader.get_prg_ram_size();
    // m_chr_rom_size = file_reader.get_chr_rom_size();

    // m_mapper = file_reader.get_mapper();

    // m_flag_nametable_arrangement = file_reader.get_nametable_arrangement();
    // m_flag_alt_nametable_arrangement = file_reader.get_alt_nametable_arrangement();
    // m_flag_presistent_memory = file_reader.get_presistent_memory();
    // m_flag_trainer_present = file_reader.get_trainer_present();
    // m_flag_vs_unisystem = file_reader.get_vs_unisystem();
    // m_flag_playchoice = file_reader.get_playchoice();
    // m_flag_nes_2 = file_reader.get_nes_2();

    ines_mappers[m_file_reader.get_mapper()](*this);
}

Cartridge::~Cartridge() {
    for(auto component : m_components) {
        delete component;
    }
}

std::map<uint8_t, std::function<void(Cartridge&)>> Cartridge::ines_mappers = {
    {0x00, setup_nrom},
};

void Cartridge::setup_nrom(Cartridge& cartridge) {
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
        Bus::instance().add_component(*prg_ram_ptr, addr);
    }

    for(int addr = 0x8000; addr < 0xBFFF; addr += prg_rom_size) {
        Bus::instance().add_component(*prg_rom_ptr, addr);
    }
}
