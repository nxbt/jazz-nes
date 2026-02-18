#pragma once

#include <bus_component.h>

#include <cstdint>
#include <vector>

class Rom: public BusComponent {
public:
    Rom(uint16_t size);

    uint8_t read_data(uint16_t addr_local) override;
    void write_data(uint16_t addr_local, uint8_t data) override;

private:
    std::vector<uint8_t> m_memory;
};