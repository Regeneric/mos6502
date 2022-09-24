#pragma once

#include <cstdint>
#include <array>

#include "CPU.hpp"

using Word = uint16_t;
using Byte = uint8_t;

class Bus {

public:
    Bus();
    ~Bus();

    CPU cpu;
    std::array<Byte, 64*1024> RAM;      // Fake RAM

    void write(Word address, Byte data);
    Byte read(Word address, bool readOnly = false);
};