#pragma once

#include <cstdint>

class Bus {
public:
    uint16_t cpu_address;
    uint8_t cpu_data;

    uint16_t ppu_address;
    uint8_t ppu_data;
};