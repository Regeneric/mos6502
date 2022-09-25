#include "headers/Bus.hpp"

Bus::Bus() {cpu.busConnector(this);} 
Bus::~Bus(){}


void Bus::insertCart(const std::shared_ptr<Cart> &_cart) {
    this->cart = _cart;
    ppu.connectCart(cart);

    return;
}


void Bus::cpuWrite(Word address, Byte data) {
    // Unused - may be used to add new functions to emulation
    if(cart->cpuWrite(address, data)) {}
    if(address >= 0x0000 && address <= 0x1FFF) cpuRAM[address & 0x07FF] = data;  // Mapping whole range to only 2KB
    if(address >= 0x2000 && address <= 0x3FFF) ppu.cpuWrite(address & 0x0007, data);   // Mapping whole range to PPU range

    return;
}

Byte Bus::cpuRead(Word address, bool readOnly) {
    Byte data;

    if(cart->cpuRead(address, data)) {}
    if(address >= 0x0000 && address <= 0x1FFF) data = cpuRAM[address & 0x07FF];
    if(address >= 0x2000 && address <= 0x3FFF) data = ppu.cpuRead(address & 0x0007, readOnly);

    return data;
}


void Bus::clock() {
    ppu.clock();
    if(systemClockCounter % 3 == 0) cpu.clock();

    systemClockCounter++;
    return;
}

void Bus::reset() {
    cpu.reset();
    systemClockCounter = 0;
}