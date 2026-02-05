#pragma once

#include "bus.h"

class Cpu {
private:
    Bus& m_bus;

public:
    Cpu(Bus &bus);
};