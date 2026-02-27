#pragma once

#include "rom.h"

#include "file_reader.h"

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

class BusComponent;
class Nes;

class Cartridge {
public:
    Cartridge() = delete;
    Cartridge(std::string file_path);
    ~Cartridge();

    void connect(Nes& nes);

    FileReader m_file_reader;

private:
    std::ifstream m_ifstream;
    std::vector<BusComponent*> m_components;

    BusComponent* add_component(BusComponent* component_ptr);

    static std::map<uint8_t, std::function<void(Cartridge&, Nes&)>> ines_mappers;

    static void setup_nrom(Cartridge&, Nes&);
};