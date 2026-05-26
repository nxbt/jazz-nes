#include "bus.h"

#include "bus_component.h"

#include <iostream>
#include <iomanip>

Bus::Bus() {}

void Bus::add_component(BusComponent& component, uint16_t start_addr) {
    m_components.insert({start_addr, component});
}

uint8_t Bus::read_data(uint16_t addr) {
    int components_hit = 0;

    for(auto itr = m_components.begin(); itr != m_components.end(); ++itr) {
        auto& [addr_offset, component] = *itr;

        if(addr_offset > addr) break;
        if(addr_offset + component.m_size <= addr) continue;

        if(++components_hit > 1) { std::cerr << "WARNING: read_data bus conflict at 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << "\n"; }

        m_data = component.read_from(addr - addr_offset);
    }

    if(components_hit == 0) { std::cerr << "WARNING: read_data open bus at 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << "\n"; }

    return m_data;
}

void Bus::write_data(uint16_t addr, uint8_t data) {
    int components_hit = 0;

    m_data = data;

    for(auto itr = m_components.begin(); itr != m_components.end(); ++itr) {
        auto& [addr_offset, component] = *itr;

        if(addr_offset > addr) break;
        if(addr_offset + component.m_size < addr) continue;

        if(++components_hit > 1) { std::cerr << "WARNING: write_data overloaded at 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << "\n"; }

        component.write_to(addr - addr_offset, data);
    }

    if(components_hit == 0) { std::cerr << "WARNING: write_data to unmapped memory at 0x" << std::hex << std::setw(4) << std::setfill('0') << addr << "\n"; }
}