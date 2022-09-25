#pragma once

#include <cstdint>

using Dword = uint32_t;
using Word = uint16_t;
using Byte = uint8_t;

class Mapper {
public:
    Mapper(Byte _prgBanks, Byte _chrBanks);
    ~Mapper();

    virtual bool cpuMapRead(Word address, Dword &mappedAddress)  = 0;
    virtual bool cpuMapWrite(Word address, Dword &mappedAddress) = 0;

    virtual bool ppuMapRead(Word address, Dword &mappedAddress)  = 0;
    virtual bool ppuMapWrite(Word address, Dword &mappedAddress) = 0;

protected:
    Byte prgBanks = 0;
    Byte chrBanks = 0;
};