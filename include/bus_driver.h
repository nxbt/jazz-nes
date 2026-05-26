#pragma once

#include <cinttypes>

class Bus;
class BusComponent;

/*
 * Base class for any component that drives a data/address bus
 * Generally the CPU or PPU
 */
class BusDriver {
public:
    ~BusDriver();

    void write_data(uint16_t addr, uint8_t data);
    uint8_t read_data(uint16_t addr);

    void add_bus_component(BusComponent& component, uint16_t start_addr);

    BusDriver(BusDriver const&) = delete;
    void operator=(BusDriver const&) = delete;

protected:
    BusDriver();

private:
    Bus* m_bus_ptr;
};
