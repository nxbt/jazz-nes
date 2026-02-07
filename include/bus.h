#pragma once

#include <cstdint>

class Bus {
public:
    Bus();
    ~Bus();

    uint16_t m_address;
    uint8_t m_data;

    const uint16_t read_address() { return m_address; }
    const uint8_t read_data() { return m_data; }

    void write_address(const uint16_t);
    void write_data(const uint8_t);

private:

};