#include "headers/Bus.hpp"

Bus::Bus() {
    cpu.busConnector(this);
    for(auto &r : RAM) r = 0x00;
} Bus::~Bus(){}


void Bus::write(Word address, Byte data) {
    if(address >= 0x0000 && address <= 0xFFFF) 
        RAM[address] = data;
}

Byte Bus::read(Word address, bool readOnly) {
    if(address >= 0x0000 && address <= 0xFFFF) 
        return RAM[address];

    return 0x00;
}