#pragma once

#include <cstdint>
#include <map>

class BusComponent;
class Cpu;

class Bus {
public:
    Bus();
    ~Bus();

    uint16_t m_address;
    uint8_t m_data;

    std::multimap<uint16_t, BusComponent&> m_components;

    void add_component(BusComponent& component, uint16_t start_addr);

    uint8_t read_data(uint16_t addr);
    void write_data(uint16_t addr, uint8_t data);

private:

};