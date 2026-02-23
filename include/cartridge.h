#pragma once

#include "rom.h"

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

class BusComponent;

class Cartridge {
public:
    Cartridge() = delete;
    Cartridge(std::string file_path);
    ~Cartridge();

    void connect_cartridge();

    uint8_t m_prg_rom_size;
    uint8_t m_prg_ram_size;
    uint8_t m_chr_rom_size;

    uint8_t m_mapper;

    bool m_flag_nametable_arrangement;
    bool m_flag_alt_nametable_arrangement;
    bool m_flag_presistent_memory;
    bool m_flag_trainer_present;
    bool m_flag_vs_unisystem;
    bool m_flag_playchoice;
    bool m_flag_nes_2;

private:
    std::ifstream m_ifstream;
    std::vector<BusComponent*> m_components;

    static std::map<uint8_t, std::function<void(Cartridge&)>> ines_mappers;

    static void setup_nrom(Cartridge&);
};