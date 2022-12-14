#pragma once

#include <cstdint>
#include <array>

#include "CPU.hpp"
#include "PPU.hpp"
#include "Cart.hpp"

using Dword = uint32_t;
using Word = uint16_t;
using Byte = uint8_t;

class Bus {
public:
    Bus();
    ~Bus();

    CPU cpu;
    PPU ppu;
    std::array<Byte, 2048> cpuRAM;      // Fake RAM
    std::shared_ptr<Cart> cart;

    void clock();
    void reset();

    void cpuWrite(Word address, Byte data);
    Byte cpuRead(Word address, bool readOnly = false);

    void insertCart(const std::shared_ptr<Cart> &_cart);

private:
    Dword systemClockCnt = 0;
};