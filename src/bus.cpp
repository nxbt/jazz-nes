#include "bus.h"

Bus::Bus() {

}

Bus::~Bus() {

}

uint16_t Bus::read_address() { return m_address; }
uint8_t Bus::read_data() { return m_data; }
uint8_t Bus::read_data(uint16_t address) {
    write_address(address);
    return read_data();
}

void Bus::write_address(uint16_t address) {} //TODO
void Bus::write_data(uint8_t data) {} //TODO
void Bus::write_data(uint16_t address, uint8_t data) {
    write_address(address);
    write_data(data);
}