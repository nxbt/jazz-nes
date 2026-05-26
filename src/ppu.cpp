#include "ppu.h"

Ppu::Ppu(): BusComponent(0x0008) {

}

void Ppu::tick() {

}

void Ppu::write_to(uint16_t addr, uint8_t data) {
    BusDriver::write_data(addr & 0x3F, data);
}

uint8_t Ppu::read_from(uint16_t addr) {
    return BusDriver::read_data(addr & 0x3F);
}
