#include "headers/Cart.hpp"

Cart::Cart(const std::string &fileName) {
    // iNES mapper header
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
    std::ifstream ifs;
    ifs.open(fileName, std::ifstream::binary);
    if(ifs.is_open()) {
        ifs.read((char*)&header, sizeof(Header));

        // If "dummy" mapper is present, we're reading 512 bytes past it
        if(header.mapperOne & 0x04) ifs.seekg(512, std::ios_base::cur);
    
        mapperID = ((header.mapperOne >> 4) << 4) | (header.mapperOne >> 4);
        mirror = (header.mapperOne & 0x01) ? VERTICAL : HORIZONTAL;

        Byte fileType = 1;
        if(fileType == 0) {}
        if(fileType == 1) {
            prgBanks = header.prgROMChunks;
            prgMem.resize(prgBanks*16384);
            ifs.read((char*)prgMem.data(), prgMem.size());

            chrBanks = header.chrROMChunks;
            chrMem.resize(chrBanks*8192);
            ifs.read((char*)chrMem.data(), chrMem.size());
        }
        if(fileType == 2) {}

        switch(mapperID) {
            case 0: mapper = std::make_shared<Mapper_0>(prgBanks, chrBanks); break;
        }

        imageValid = true;
        ifs.close();
    }
} Cart::~Cart(){}


bool Cart::image(){return imageValid;}

bool Cart::cpuWrite(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->cpuMapWrite(address, mappedAddress)) {
        prgMem[mappedAddress] = data;
        return true;
    } return false;
}
bool Cart::cpuRead(Word addres, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->cpuMapRead(addres, mappedAddress)) {
        data = prgMem[mappedAddress];
        return true;
    } return false;
}

bool Cart::ppuWrite(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->ppuMapWrite(address, mappedAddress)) {
        chrMem[mappedAddress] = data;
        return true;
    } return false;
}
bool Cart::ppuRead(Word address, Byte &data) {
    Dword mappedAddress = 0;
    if(mapper->ppuMapRead(address, mappedAddress)) {
        data = chrMem[mappedAddress];
        return true;
    } return false;
}