#pragma once

#include "Mapper.hpp"

class Mapper_0 : public Mapper {
public:
	Mapper_0(Byte _prgBanks, Byte _chrBanks);
	~Mapper_0();

public:
	bool cpuMapRead(Word address, Dword &mappedAddress)  override;
	bool cpuMapWrite(Word address, Dword &mappedAddress) override;
	bool ppuMapRead(Word address, Dword &mappedAddress)  override;
	bool ppuMapWrite(Word address, Dword &mappedAddress) override;
};