#include <ram.h>

#include <bus.h>

#include <cstdint>

Ram::Ram(uint16_t size): BusComponent(size) {
    m_memory.resize(m_size);
}

uint8_t Ram::read_data(uint16_t addr_local) {
    return m_memory[addr_local];
}

void Ram::write_data(uint16_t addr_local, uint8_t data) {
    m_memory[addr_local] = data;
}
