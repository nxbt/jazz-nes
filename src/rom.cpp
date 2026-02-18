#include <rom.h>

#include <bus.h>

#include <cstdint>
#include <iostream>

Rom::Rom(uint16_t size): BusComponent(size) {
    m_memory.resize(m_size);
}

uint8_t Rom::read_data(uint16_t addr_local) {
    return m_memory[addr_local];
}

void Rom::write_data(uint16_t addr_local, uint8_t data) {
    std::cerr << "WARNING: write_data to ROM ignored at " << addr_local;
}