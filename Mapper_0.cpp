#include "headers/Mapper_0.hpp"

Mapper_0::Mapper_0(Byte _prgBanks, Byte _chrBanks) : Mapper(prgBanks, chrBanks) {}
Mapper_0::~Mapper_0() {}

bool Mapper_0::cpuMapRead(Word address, Dword &mappedAddress) {
	// // if PRGROM is 16KB
	// //     CPU Address Bus          PRG ROM
	// //     0x8000 -> 0xBFFF: Map    0x0000 -> 0x3FFF
	// //     0xC000 -> 0xFFFF: Mirror 0x0000 -> 0x3FFF
	// // if PRGROM is 32KB
	// //     CPU Address Bus          PRG ROM
	// //     0x8000 -> 0xFFFF: Map    0x0000 -> 0x7FFF	

	if(address >= 0x8000 && address <= 0xFFFF) {
		mappedAddress = address & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	} return false;
}
bool Mapper_0::cpuMapWrite(Word address, Dword &mappedAddress) {
    if(address >= 0x8000 && address <= 0xFFFF) {
        mappedAddress = address & (prgBanks > 1 ? 0x7FFF : 0x3FFF);
        return true;
    } return false;
}

bool Mapper_0::ppuMapRead(Word address, Dword &mappedAddress) {
    if(address >= 0x0000 && address <= 0x1FFF) {
        mappedAddress = address;
        return true;
    } return false;
}
bool Mapper_0::ppuMapWrite(Word address, Dword &mappedAddress) {
    if(address >= 0x0000 && address <= 0x1FFF) {
        if(chrBanks == 0) {
            mappedAddress = address;
            return true;
        }
    } return false;
}