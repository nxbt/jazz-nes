#pragma once

#include <fstream>
#include <vector>
#include <cstdint>

class Cartridge;

/*
 * Reads iNES files and parses the content.
 */
class FileReader {
public:
    FileReader() = delete;
    FileReader(std::string file_path);

    std::vector<uint8_t> get_prg_rom();
    std::vector<uint8_t> get_chr_rom();

    int get_prg_rom_size();
    int get_prg_ram_size();
    int get_chr_rom_size();

    uint8_t get_mapper();

    bool get_nametable_arrangement();
    bool get_alt_nametable_arrangement();
    bool get_presistent_memory();
    bool get_trainer_present();
    bool get_vs_unisystem();
    bool get_playchoice();
    bool get_nes_2();

private:
    std::vector<uint8_t> m_buffer;

    static void error_open(std::string file_path);
    static void error_file_type(std::string file_path);
};
