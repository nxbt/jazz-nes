#pragma once

class Bus;

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
