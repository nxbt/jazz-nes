#include <rom.h>

#include <bus.h>

#include <cstdint>
#include <iostream>

Rom::Rom(uint16_t size, const std::vector<uint8_t>& data): BusComponent(size) {
    m_memory = data;

    if(m_memory.size() != size) {
        std::cerr << "WARNING: ROM initilized with size " << size << 
            " but data is actually size " << m_memory.size() << "\n";
    
        m_memory.resize(size);
    }
}

uint8_t Rom::read_data(uint16_t addr_local) {
    return m_memory[addr_local];
}

void Rom::write_data(uint16_t addr_local, uint8_t data) {
    std::cerr << "WARNING: attempt to write data to ROM ignored";
}
