#include "cartridge.h"

#include <iostream>

Cartridge::Cartridge(std::string file_path) {
    read_file(file_path);
}

std::map<uint8_t, std::function<void(Cartridge&)>> Cartridge::ines_mappers = {
    {0x00, setup_nrom},
};

void Cartridge::read_file(std::string file_path) {
    m_ifstream.exceptions(std::ios_base::failbit);

    try {
        m_ifstream.open(file_path);
    }
    catch(const std::ios_base::failure& e) {
        error_open(file_path);
    }

    uint8_t header[16];

    try {
        m_ifstream.read(reinterpret_cast<char*>(&header), sizeof(header));
    }
    catch(const std::ios_base::failure& e) {
        error_file_type(file_path);
    }

    if( // assert file starts with "NES<EOF>"
        header[0] != 0x4E || 
        header[1] != 0x45 ||
        header[2] != 0x53 ||
        header[3] != 0x1A
    ) {
        error_file_type(file_path);
    }
    

}

void Cartridge::error_open(std::string file_path) {
    std::cerr << "failed to open \"" << file_path << "\"\n";
    std::exit(EXIT_FAILURE);
}

void Cartridge::error_file_type(std::string file_path) {
    std::cerr << "\"" << file_path << "\" is not an iNES file\n";
    std::exit(EXIT_FAILURE);
}

void setup_nrom(Cartridge& cartridge) {}
