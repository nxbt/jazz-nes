#include "bus_driver.h"

#include "bus.h"

BusDriver::BusDriver() {
    m_bus_ptr = new Bus();
}

BusDriver::~BusDriver() {
    delete m_bus_ptr;
}

Bus& BusDriver::bus() {
    return *m_bus_ptr;
}
