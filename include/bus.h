#pragma once

#include <cstdint>

class Bus {
public:
    Bus();
    ~Bus();

    uint16_t m_address;
    uint8_t m_data;

    uint16_t read_address();
    uint8_t read_data();
    uint8_t read_data(uint16_t address);

    void write_address(uint16_t address);
    void write_data(uint8_t data);
    void write_data(uint16_t address, uint8_t data);

private:

};