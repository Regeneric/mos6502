#pragma once

#include "Mapper.hpp"

class _Mapper : public Mapper {
public:
	_Mapper(Byte _prgBanks, Byte _chrBanks);
	~_Mapper();

public:
	bool cpuMapRead(Word address, Dword &mappedAddress)  override;
	bool cpuMapWrite(Word address, Dword &mappedAddress) override;
	bool ppuMapRead(Word address, Dword &mappedAddress)  override;
	bool ppuMapWrite(Word address, Dword &mappedAddress) override;
};