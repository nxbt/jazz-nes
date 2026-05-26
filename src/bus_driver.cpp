#include "bus_driver.h"

#include "bus.h"

BusDriver::BusDriver() {
    m_bus_ptr = new Bus();
}

BusDriver::~BusDriver() {
    delete m_bus_ptr;
}

void BusDriver::write_data(uint16_t addr, uint8_t data) {
    m_bus_ptr->write_data(addr, data);
}

uint8_t BusDriver::read_data(uint16_t addr) {
    return m_bus_ptr->read_data(addr);
}

void BusDriver::add_bus_component(BusComponent& component, uint16_t start_addr) {
    m_bus_ptr->add_component(component, start_addr);
}
