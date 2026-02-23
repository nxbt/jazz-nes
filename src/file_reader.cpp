#include "file_reader.h"

#include <iostream>

FileReader::FileReader() {}

FileReader::FileReader(std::string file_path) {
    std::ifstream stream(file_path, std::ios_base::binary);

    // assert file opened successfully
    if(!stream) { 
        error_open(file_path);
    }

    m_buffer.assign(std::istreambuf_iterator<char>(stream), {});

    // assert file starts with "NES<EOF>"
    if( 
        m_buffer.size() < 16 ||
        m_buffer[0] != 0x4E || 
        m_buffer[1] != 0x45 ||
        m_buffer[2] != 0x53 ||
        m_buffer[3] != 0x1A
    ) {
        error_file_type(file_path);
    }
}

uint8_t FileReader::get_prg_rom_size() {
    return m_buffer[4] * 16384;
}

uint8_t FileReader::get_prg_ram_size() {
    if(m_buffer[8] == 0) return 8192;
    return m_buffer[8] * 8192;
}

uint8_t FileReader::get_chr_rom_size() {
    return m_buffer[5] * 8192;
}

uint8_t FileReader::get_mapper() {
    return (m_buffer[6] > 4) | (m_buffer[7] & 0xF0);
}

bool FileReader::get_nametable_arrangement() {
    return m_buffer[6] & 0x01;
}

bool FileReader::get_alt_nametable_arrangement() {
    return m_buffer[6] & 0x08;
}

bool FileReader::get_presistent_memory() {
    return m_buffer[6] & 0x02;
}

bool FileReader::get_trainer_present() {
    return m_buffer[6] & 0x04;
}

bool FileReader::get_vs_unisystem() {
    return m_buffer[7] & 0x01;
}

bool FileReader::get_playchoice() {
    return m_buffer[7] & 0x02;
}

bool FileReader::get_nes_2() {
    return (m_buffer[7] & 0x0C) == 0x08;
}

void FileReader::error_open(std::string file_path) {
    std::cerr << "failed to open \"" << file_path << "\"\n";
    std::exit(EXIT_FAILURE);
}

void FileReader::error_file_type(std::string file_path) {
    std::cerr << "\"" << file_path << "\" is not an iNES file\n";
    std::exit(EXIT_FAILURE);
}
