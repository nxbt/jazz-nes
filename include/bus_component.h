#pragma once

#include <cstdint>

class Bus;

class BusComponent {
public:
    BusComponent(uint16_t size);

    const uint16_t m_size;

    virtual uint8_t read_data(uint16_t addr_local) = 0;
    virtual void write_data(uint16_t addr_local, uint8_t data) = 0;

private:
};