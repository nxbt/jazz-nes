#pragma once

#include <cinttypes>

#include "bus_driver.h"
#include "bus_component.h"

class Ppu: BusDriver, BusComponent {
public:
    Ppu();

    void tick();

    // read and write overwritten to truncate to 14-bit address
    void write_to(uint16_t addr, uint8_t data) override;
    uint8_t read_from(uint16_t addr) override;

    Ppu(Ppu const&) = delete;
    void operator=(Ppu const&) = delete;

private:
    uint8_t m_oam_addr;
    uint8_t m_oam_data;
    uint8_t m_scroll_x;
    uint8_t m_scroll_y;
    uint16_t m_ppu_addr;
    uint8_t m_ppu_data;
    uint8_t m_oam_dma;

};