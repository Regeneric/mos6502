#include "headers/Mapper.hpp"

Mapper::Mapper(uint8_t _prgBanks, uint8_t _chrBanks) {
	prgBank = _prgBanks;
	chrBank = _chrBanks;
} Mapper::~Mapper(){}