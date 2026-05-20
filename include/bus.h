#pragma once

#include <cstdint>
#include <map>

class BusComponent;

/*
 * Representation of a paired 16-bit address bus and 8-bit data bus
 */
class Bus {
public:
    Bus();

    uint16_t m_address;
    uint8_t m_data;

    // map of components connected to the bus, indexed by starting address
    std::multimap<uint16_t, BusComponent&> m_components;

    void add_component(BusComponent& component, uint16_t start_addr);

    uint8_t read_data(uint16_t addr);
    void write_data(uint16_t addr, uint8_t data);

    Bus(Bus const&) = delete;
    void operator=(Bus const&) = delete;

private:
};