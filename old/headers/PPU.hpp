#pragma once

#include <cstdint>
#include <memory>

#include "../olcPixelGameEngine.h"
#include "Cart.hpp"

using Word = uint16_t;
using Byte = uint8_t;

class PPU {
public:
    PPU();
    ~PPU();

    Byte tableName[2][1024];
    Byte tablePattern[2][4096];
    Byte tablePalette[32];

	// Debugging Utilities
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(Byte i);
	olc::Sprite& GetPatternTable(Byte i);
	bool frame_complete = false;

	// Communications with Main Bus
	Byte cpuRead(Word address, bool readOnly = false);
	void cpuWrite(Word address, Byte data);

	// Communications with PPU Bus
	Byte ppuRead(Word address, bool readOnly = false);
	void ppuWrite(Word address, Byte data);

    void connectCart(const std::shared_ptr<Cart> &_cart);
    void clock();

private:
	olc::Pixel  palScreen[0x40];
	olc::Sprite sprScreen;
	olc::Sprite sprNameTable[2];
	olc::Sprite sprPatternTable[2];

    Word scanLine = 0;
    Word cycle = 0;

    std::shared_ptr<Cart> cart;
};