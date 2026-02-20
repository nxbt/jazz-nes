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
    Cartridge(std::string);

    void connect_cartridge();

private:
    std::ifstream m_ifstream;
    std::vector<BusComponent> m_components;

    void read_file(std::string file_path);

    static std::map<uint8_t, std::function<void(Cartridge&)>> ines_mappers;

    static void error_open(std::string file_path);
    static void error_file_type(std::string file_path);

    static void setup_nrom(Cartridge&);
};