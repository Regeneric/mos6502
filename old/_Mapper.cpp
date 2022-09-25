#include "headers/_Mapper.hpp"

_Mapper::_Mapper(Byte _prgBank, Byte _chrBank) : Mapper(prgBank, chrBank) {}
_Mapper::~_Mapper() {}

bool _Mapper::cpuMapRead(Word address, Dword &mappedAddress) {
	// // if PRGROM is 16KB
	// //     CPU Address Bus          PRG ROM
	// //     0x8000 -> 0xBFFF: Map    0x0000 -> 0x3FFF
	// //     0xC000 -> 0xFFFF: Mirror 0x0000 -> 0x3FFF
	// // if PRGROM is 32KB
	// //     CPU Address Bus          PRG ROM
	// //     0x8000 -> 0xFFFF: Map    0x0000 -> 0x7FFF	

	// if(address >= 0x8000 && address <= 0xFFFF) {
	// 	mappedAddress = address & (prgBank > 1 ? 0x7FFF : 0x3FFF);
	// 	return true;
	// } else return false;
    return false;
}
bool _Mapper::cpuMapWrite(Word address, Dword &mappedAddress) {
    if(address >= 0x8000 && address <= 0xFFFF) {
        mappedAddress = address & (prgBank > 1 ? 0x7FFF : 0x3FFF);
        return true;
    } else return false;
}

bool _Mapper::ppuMapRead(Word address, Dword &mappedAddress) {
    if(address >= 0x0000 && address <= 0x1FFF) {
        mappedAddress = address;
        return true;
    } else return false;
}
bool _Mapper::ppuMapWrite(Word address, Dword &mappedAddress) {
    if(address >= 0x0000 && address <= 0x1FFF) {
        if(chrBank == 0) {
            mappedAddress = address;
            return true;
        }
    } else return false;
}