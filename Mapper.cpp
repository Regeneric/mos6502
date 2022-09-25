#include "headers/Mapper.hpp"

Mapper::Mapper(uint8_t _prgBanks, uint8_t _chrBanks) {
	prgBanks = _prgBanks;
	chrBanks = _chrBanks;
} Mapper::~Mapper(){}