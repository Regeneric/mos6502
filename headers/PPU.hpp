#pragma once

#include "Cart.hpp"

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

using Word = uint16_t;
using Byte = uint8_t;

class PPU {    
public:
    PPU();
    ~PPU();

    bool frameComplete = false;

    Byte tableName[2][1024];
    Byte tablePattern[2][4096];
    Byte tablePalette[32];

    // Main Bus communication
    void cpuWrite(Word address, Byte data);
    Byte cpuRead(Word address, bool readOnly = false);

    // PPU Bus communication
    void ppuWrite(Word address, Byte data);
    Byte ppuRead(Word address, bool readOnly = false);

    void connectCart(const std::shared_ptr<Cart> &_cart);
    void clock();
private:
    sf::Color palScreen[0x40];

    Word cycle = 0;
    Word scanLine = 0;

    std::shared_ptr<Cart> cart;
};