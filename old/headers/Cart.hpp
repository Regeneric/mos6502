#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "Mapper_0.hpp"

using Dword = uint32_t;
using Word = uint16_t;
using Byte = uint8_t;

class Cart {
public:
    Cart(const std::string& fileName);
    ~Cart();

    bool image();

    enum MIRROR {
        HORIZONTAL,
        VERTICAL,
        ONSCREEN_LO,
        ONSCREEN_HI,
    } mirror = HORIZONTAL;

    // Main Bus communication
    bool cpuRead(Word address, Byte &data);
    bool cpuWrite(Word address, Byte &data);

    // PPU Bus communication
    bool ppuRead(Word address, Byte &data);
    bool ppuWrite(Word address, Byte &data);

private:
    bool imageValid = false;

    Byte mapperID = 0;
    Byte prgBank  = 0;
    Byte chrBank  = 0;

    std::vector<Byte> prgMem;
    std::vector<Byte> chrMem;

    std::shared_ptr<Mapper> mapper;
};