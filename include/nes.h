#pragma once

#include <string>

class Bus;
class Cpu;
class Cartridge;
class Ram;

class Nes {
public:
    Nes();
    ~Nes();

    void start();
    void stop();
    void restart();

    void load_cartridge(std::string file_path);

    Cpu& cpu();

    Cartridge& cartridge();

private:
    Cpu* m_cpu_ptr;

    Ram* m_onboard_ram_ptr;

    Cartridge* m_cartridge_ptr;
};
