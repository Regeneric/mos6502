#pragma once

#include "Mapper_0.hpp"

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

using Dword = uint32_t;
using Word = uint16_t;
using Byte = u_int8_t;

class Cart {
public:
    Cart(const std::string &fileName);
    ~Cart();

    enum MIRROR {
        HORIZONTAL,
        VERTICAL,
        ONSCREEN_LO,
        ONSCREEN_HI,
    } mirror = HORIZONTAL;

    bool image();

    // Main Bus communication
    bool cpuWrite(Word address, Byte &data);
    bool cpuRead(Word address, Byte &data);

    // PPU Bus communication
    bool ppuWrite(Word address, Byte &data);
    bool ppuRead(Word address, Byte &data);

private:
    bool imageValid = false;

    Byte mapperID = 0;
    Byte prgBanks = 0;
    Byte chrBanks = 0;

    std::vector<Byte> prgMem;
    std::vector<Byte> chrMem;

    std::shared_ptr<Mapper> mapper;
};