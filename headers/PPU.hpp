#pragma once

#include "Cart.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstdint>
#include <cstdlib>
#include <memory>

using Word = uint16_t;
using Byte = uint8_t;

class PPU {    
public:
    PPU();
    ~PPU();

    static const int W = 680, H = 480;
    bool frameComplete = false;

    // sf::Texture texture;
    // sf::Uint8 *pixels = new sf::Uint8[W*H*4];

    // sf::Sprite &screen();
    std::vector<sf::Vertex> &screen();
    // std::vector<sf::RectangleShape> &screen();
    sf::Sprite &nameTable(Byte i);
    sf::Sprite &patternTable(Byte i);

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
    sf::Sprite sprNameTable[2];
    sf::Sprite sprPatternTable[2];

    std::vector<sf::Vertex> sprScreen;
    // std::vector<sf::RectangleShape> sprScreen;

    Word cycle = 0;
    Word scanLine = 0;

    std::shared_ptr<Cart> cart;
};