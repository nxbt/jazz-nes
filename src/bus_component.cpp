#include <bus_component.h>

#include <bus.h>

#include <cstdint>

BusComponent::BusComponent(uint16_t size): m_bus(Bus::instance()), m_size(size) {}
