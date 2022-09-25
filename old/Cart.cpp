#include "headers/Cart.hpp"

Cart::Cart(const std::string& fileName) {
    // iNES Mapper header
    struct Header {
        char name[4];
        Byte prgROMChunks;
        Byte chrROMChunks;
        Byte mapperOne;
        Byte mapperTwo;
        Byte prgRAMSize;
        Byte tvSystemOne;
        Byte tvSystemTwo;
        char unused[5];
    } header;
    
    imageValid = false;

    std::ifstream input;
    input.open(fileName, std::ifstream::binary);
    if(input.is_open()) {
        input.read((char*)&header, sizeof(Header));

        // If dummy mapper exists in header, we're reading past it
        if(header.mapperOne & 0x04) input.seekg(512, std::ios_base::cur);

        mapperID = ((header.mapperTwo >> 4) << 4) | (header.mapperOne >> 4);
        mirror = (header.mapperOne & 0x01) ? VERTICAL : HORIZONTAL;

        Byte fileType = 1;
        if(fileType == 0) {}
        if(fileType == 1) {
            prgBank = header.prgROMChunks;
            prgMem.resize(prgBank*16384);
            input.read((char*)prgMem.data(), prgMem.size());

            chrBank = header.chrROMChunks;
            chrMem.resize(chrBank*8192);
            input.read((char*)chrMem.data(), chrMem.size());
        }
        if(fileType == 2) {}

        switch(mapperID) {
            case 0: mapper = std::make_shared<_Mapper>(prgBank, chrBank); break;
        }

        imageValid = true;
        input.close();
    }
} Cart::~Cart(){}


bool Cart::image(){return imageValid;}

bool Cart::cpuRead(Word address, Byte &data) {
    // Dword mappedAddress = 0;
    // if(mapper->cpuMapRead(address, mappedAddress)) {
    //     data = prgMem[mappedAddress];
    //     return true;
    // } else return false;

    return false;
}
bool Cart::cpuWrite(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->cpuMapWrite(address, mappedAddress)) {
        prgMem[mappedAddress] = data;
        return true;
    } else return false;
}

bool Cart::ppuRead(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->ppuMapRead(address, mappedAddress)) {
        data = chrMem[mappedAddress];
        return true;
    } else return false;
}
bool Cart::ppuWrite(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->ppuMapWrite(address, mappedAddress)) {
        chrMem[mappedAddress] = data;
        return true;
    } else return false;
}