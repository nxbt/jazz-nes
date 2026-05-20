#pragma once

class Bus;

/*
 * Base class for any component that drives a data/address bus
 * Generally the CPU or PPU
 */
class BusDriver {
public:
    ~BusDriver();

    Bus& bus();

    BusDriver(BusDriver const&) = delete;
    void operator=(BusDriver const&) = delete;

protected:
    BusDriver();

private:
    Bus* m_bus_ptr;
};
