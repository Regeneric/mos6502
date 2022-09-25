#include "headers/PPU.hpp"

PPU::PPU(){
    palScreen[0x00] = sf::Color(84, 84, 84);
	palScreen[0x01] = sf::Color(0, 30, 116);
	palScreen[0x02] = sf::Color(8, 16, 144);
	palScreen[0x03] = sf::Color(48, 0, 136);
	palScreen[0x04] = sf::Color(68, 0, 100);
	palScreen[0x05] = sf::Color(92, 0, 48);
	palScreen[0x06] = sf::Color(84, 4, 0);
	palScreen[0x07] = sf::Color(60, 24, 0);
	palScreen[0x08] = sf::Color(32, 42, 0);
	palScreen[0x09] = sf::Color(8, 58, 0);
	palScreen[0x0A] = sf::Color(0, 64, 0);
	palScreen[0x0B] = sf::Color(0, 60, 0);
	palScreen[0x0C] = sf::Color(0, 50, 60);
	palScreen[0x0D] = sf::Color(0, 0, 0);
	palScreen[0x0E] = sf::Color(0, 0, 0);
	palScreen[0x0F] = sf::Color(0, 0, 0);

	palScreen[0x10] = sf::Color(152, 150, 152);
	palScreen[0x11] = sf::Color(8, 76, 196);
	palScreen[0x12] = sf::Color(48, 50, 236);
	palScreen[0x13] = sf::Color(92, 30, 228);
	palScreen[0x14] = sf::Color(136, 20, 176);
	palScreen[0x15] = sf::Color(160, 20, 100);
	palScreen[0x16] = sf::Color(152, 34, 32);
	palScreen[0x17] = sf::Color(120, 60, 0);
	palScreen[0x18] = sf::Color(84, 90, 0);
	palScreen[0x19] = sf::Color(40, 114, 0);
	palScreen[0x1A] = sf::Color(8, 124, 0);
	palScreen[0x1B] = sf::Color(0, 118, 40);
	palScreen[0x1C] = sf::Color(0, 102, 120);
	palScreen[0x1D] = sf::Color(0, 0, 0);
	palScreen[0x1E] = sf::Color(0, 0, 0);
	palScreen[0x1F] = sf::Color(0, 0, 0);

	palScreen[0x20] = sf::Color(236, 238, 236);
	palScreen[0x21] = sf::Color(76, 154, 236);
	palScreen[0x22] = sf::Color(120, 124, 236);
	palScreen[0x23] = sf::Color(176, 98, 236);
	palScreen[0x24] = sf::Color(228, 84, 236);
	palScreen[0x25] = sf::Color(236, 88, 180);
	palScreen[0x26] = sf::Color(236, 106, 100);
	palScreen[0x27] = sf::Color(212, 136, 32);
	palScreen[0x28] = sf::Color(160, 170, 0);
	palScreen[0x29] = sf::Color(116, 196, 0);
	palScreen[0x2A] = sf::Color(76, 208, 32);
	palScreen[0x2B] = sf::Color(56, 204, 108);
	palScreen[0x2C] = sf::Color(56, 180, 204);
	palScreen[0x2D] = sf::Color(60, 60, 60);
	palScreen[0x2E] = sf::Color(0, 0, 0);
	palScreen[0x2F] = sf::Color(0, 0, 0);

	palScreen[0x30] = sf::Color(236, 238, 236);
	palScreen[0x31] = sf::Color(168, 204, 236);
	palScreen[0x32] = sf::Color(188, 188, 236);
	palScreen[0x33] = sf::Color(212, 178, 236);
	palScreen[0x34] = sf::Color(236, 174, 236);
	palScreen[0x35] = sf::Color(236, 174, 212);
	palScreen[0x36] = sf::Color(236, 180, 176);
	palScreen[0x37] = sf::Color(228, 196, 144);
	palScreen[0x38] = sf::Color(204, 210, 120);
	palScreen[0x39] = sf::Color(180, 222, 120);
	palScreen[0x3A] = sf::Color(168, 226, 144);
	palScreen[0x3B] = sf::Color(152, 226, 180);
	palScreen[0x3C] = sf::Color(160, 214, 228);
	palScreen[0x3D] = sf::Color(160, 162, 160);
	palScreen[0x3E] = sf::Color(0, 0, 0);
	palScreen[0x3F] = sf::Color(0, 0, 0);

	// texture.create(W, H);
}
PPU::~PPU(){
	// delete [] pixels;
}

std::vector<sf::Vertex> &PPU::screen() {return sprScreen;}
// std::vector<sf::RectangleShape> &PPU::screen() {return sprScreen;}
sf::Sprite &PPU::nameTable(Byte i) {return sprNameTable[i];}
sf::Sprite &PPU::patternTable(Byte i) {return sprPatternTable[i];}

void PPU::cpuWrite(Word address, Byte data) {
    switch(address) {
        case 0x0000: break;     // Control
        case 0x0001: break;     // Mask
        case 0x0002: break;     // Status
        case 0x0003: break;     // OAM Address
        case 0x0004: break;     // OAM Data
        case 0x0005: break;     // Scroll
        case 0x0006: break;     // PPU Address
        case 0x0007: break;     // PPU Data
    }
}
Byte PPU::cpuRead(Word address, bool readOnly) {
    Byte data = 0x00;
    
    switch(address) {
        case 0x0000: break;     // Control
        case 0x0001: break;     // Mask
        case 0x0002: break;     // Status
        case 0x0003: break;     // OAM Address
        case 0x0004: break;     // OAM Data
        case 0x0005: break;     // Scroll
        case 0x0006: break;     // PPU Address
        case 0x0007: break;     // PPU Data
    } return data;
}

void PPU::ppuWrite(Word address, Byte data) {
    address &= 0x3FFF;
    if(cart->ppuWrite(address, data)) {}

    return;
}
Byte PPU::ppuRead(Word address, bool readOnly) {
    Byte data = 0x00;
    address &= 0x3FFF;

    if(cart->ppuRead(address, data)) {}
    return data;
}


void PPU::connectCart(const std::shared_ptr<Cart> &_cart) {
    this->cart = _cart;
    return;
}

void PPU::clock() {
	int randomPixel = rand() % 2 ? 0x3F : 0x30;
	sprScreen.push_back(sf::Vertex(sf::Vector2f(cycle, scanLine <= -1 ? 0 : (scanLine+1)), palScreen[randomPixel]));
	sprScreen.push_back(sf::Vertex(sf::Vector2f(cycle, scanLine <= -1 ? 0 : scanLine), palScreen[randomPixel]));
	sprScreen.push_back(sf::Vertex(sf::Vector2f((cycle+1), scanLine <= -1 ? 0 : (scanLine+1)), palScreen[randomPixel]));
	sprScreen.push_back(sf::Vertex(sf::Vector2f((cycle+1), scanLine <= -1 ? 0 : scanLine), palScreen[randomPixel]));

    // Image generation for PAL systems
    cycle++;
    if(cycle >= 341) {
        cycle = 0;
        scanLine++;
        
        if(scanLine >= 261) {
            scanLine = -1;
            frameComplete = true;
        }
    } return;
}