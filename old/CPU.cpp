#include "headers/CPU.hpp"
#include "headers/Bus.hpp"

CPU::CPU() {
	lookupTable = 
	{
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
	};
} CPU::~CPU(){}


void CPU::write(Word addres, Byte data) {
    bus->cpuWrite(addres, data);
}

Byte CPU::read(Word address) {
    return bus->cpuRead(address, false);
}


void CPU::flag(FLAGS flag, bool status) {
    if(status) SR |= flag;
    else SR &= ~flag;
}

Byte CPU::flag(FLAGS flag) {
    return ((SR & flag) > 0) ? 1 : 0;
}


void CPU::reset() {
    addressABS = 0xFFFC;

    Word loByte = read(addressABS+0);
    Word hiByte = read(addressABS+1);

    PC = (hiByte<<8) | loByte;
    A = X = Y = 0;
    SP = 0xFD;
    SR = 0x00 | UN;

    addressREL = 0x0000; 
    addressABS = 0x0000;
    fetched = 0x00;

    cycles = 8;
}

void CPU::irq() {
    // If interrupts are allowed
    if(flag(DI) == 0) {
        write(0x0100 + SP, (PC>>8) & 0x00FF); SP--;
        write(0x0100 + SP, PC & 0x00FF); SP--;

        flag(BR, 0);
        flag(UN, 1);
        flag(DI, 1);
        write(0x0100 + SP, SR); SP--;

        addressABS = 0xFFFE;
        Word loByte = read(addressABS+0);
        Word hiByte = read(addressABS+1);
        PC = (hiByte<<8) | loByte;

        cycles = 7;
    }
}

void CPU::nmi() {
    write(0x0100 + SP, (PC>>8) & 0x00FF); SP--;
    write(0x0100 + SP, PC & 0x00FF); SP--;

    flag(BR, 0);
    flag(UN, 1);
    flag(DI, 1);
    write(0x0100 + SP, SR); SP--;

    addressABS = 0xFFFA;
    Word loByte = read(addressABS+0);
    Word hiByte = read(addressABS+1);
    PC = (hiByte<<8) | loByte;

    cycles = 8;
}

void CPU::clock() {
    if(cycles == 0) {
        opcode = read(PC); 
        flag(UN, true);
        PC++;

        cycles = lookupTable[opcode].cycles;
        Byte clockCycleNeed2 = (this->*lookupTable[opcode].addrmode)();
        Byte clockCycleNeed1 = (this->*lookupTable[opcode].operate)();
        
        // If certain operation in combination with addressing mode requires additional clock cycle
        cycles += (clockCycleNeed1 & clockCycleNeed2);
        flag(UN, true);
    } cycles--;
}



// Addressing Modes
Byte CPU::IMP() {   // Implied
    fetched = A;
    return 0;
}
Byte CPU::IMM() {   // Immediate
    addressABS = PC++;
    return 0;
}
Byte CPU::ZP0() {   // Zero-Page
    addressABS = read(PC);
    PC++;
    addressABS &= 0x00FF;
    
    return 0;
}
Byte CPU::ZPX() {   // Zero-Page with Offset X
    addressABS = (read(PC) + X);
    PC++;
    addressABS &= 0x00FF;

    return 0;
}
Byte CPU::ZPY() {   // Zero-Page with Offset Y
    addressABS = (read(PC) + Y);
    PC++;
    addressABS &= 0x00FF;

    return 0;
}
Byte CPU::ABS() {   // Absolute
    Word loByte = read(PC); PC++;
    Word hiByte = read(PC); PC++;

    addressABS = (hiByte << 8) | loByte;
    return 0;
}
Byte CPU::ABX() {   // Absolute with Offset X
    Word loByte = read(PC); PC++;
    Word hiByte = read(PC); PC++;

    addressABS = (hiByte<<8) | loByte;
    addressABS += X;

    // If we change the page, we need to communicate, that we need additional clock cycle
    if((addressABS & 0xFF00) != (hiByte << 8)) return 1;
    else return 0;
}
Byte CPU::ABY() {   // Absolute with Offset Y
    Word loByte = read(PC); PC++;
    Word hiByte = read(PC); PC++;

    addressABS = (hiByte<<8) | loByte;
    addressABS += Y;

    // If we change the page, we need to communicate, that we need additional clock cycle
    if((addressABS & 0xFF00) != (hiByte << 8)) return 1;
    else return 0;
}
Byte CPU::IND() {   // Indirect
    Word loPtr = read(PC); PC++;
    Word hiPtr = read(PC); PC++;

    Word pointer = (hiPtr<<8) | loPtr;

    if(loPtr = 0x00FF) addressABS = (read(pointer & 0xFF00) << 8) | read(pointer+0);
    else addressABS = (read(pointer+1) << 8) | read(pointer);
    
    return 0;
}
Byte CPU::IZX() {   // Zero-Page Indirect with Offset X
    Word zp = read(PC); PC++;

    Word loByte = read((Word)(zp+ (Word)X) & 0x00FF);
    Word hiByte = read((Word)(zp+ (Word)X+1) & 0x00FF);

    addressABS = (hiByte<<8) | loByte;
    return 0;
}
Byte CPU::IZY() {   // Zero-Page Indirect with Offset Y
    Word zp = read(PC); PC++;

    Word loByte = read(zp & 0x00FF);
    Word hiByte = read((zp+1) & 0x00FF);

    addressABS = (hiByte<<8) | loByte;
    addressABS += Y;

    // If we change the page, we need to communicate, that we need additional clock cycle
    if((addressABS & 0x00FF) != (hiByte<<8)) return 1;
    else return 0;
}
Byte CPU::REL() {  // Relative
    addressREL = read(PC); PC++;
    if(addressREL & 0x80) addressREL |= 0xFF00;

    return 0;
}


// Instructions
Byte CPU::fetch() {
    if(!(lookupTable[opcode].addrmode == &CPU::IMP)) 
        fetched = read(addressABS);
    
    return fetched;
}


Byte CPU::AND() {
    fetch();
    A = A & fetched;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 1;
}
Byte CPU::ASL() {
    fetch();
    Word bufer = (Word)fetched << 1;

    flag(CB, (bufer & 0xFF00) > 0);
    flag(ZF, (bufer & 0x00FF) == 0x00);
    flag(NG, bufer & 0x80);

    if(lookupTable[opcode].addrmode == &CPU::IMP) A = bufer & 0x00FF;
    else write(addressABS, bufer & 0x00FF);

    return 0;
}


Byte CPU::BCS() {
    if(flag(CB) == 1) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BCC() {
    if(flag(CB) == 0) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BEQ() {
    if(flag(ZF) == 1) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BMI() {
    if(flag(NG) == 1) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BNE() {
    if(flag(ZF) == 0) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BPL() {
    if(flag(NG) == 0) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BVC() {
    if(flag(OV) == 0) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BVS() {
    if(flag(OV) == 1) {
        cycles++;
        addressABS = PC + addressREL;

        if((addressABS & 0xFF00) != (PC & 0xFF00)) cycles++;
        PC = addressABS;
    } return 0;
}
Byte CPU::BIT() {
    fetch();
    Word bufer = A & fetched;

    flag(ZF, (bufer & 0x00FF) == 0x00);
    flag(NG, fetched & (1<<7));
    flag(OV, fetched & (1<<8));

    return 0;
}
Byte CPU::BRK() {
    PC++;

    flag(DI, 1);
    write(0x0100 + SP, (PC>>8) & 0x00FF); SP--;
    write(0x0100 + SP, PC & 0x00FF); SP--;

    flag(BR, 1);
    write(0x0100 + SP, SR); SP--;
    flag(BR, 0);

    PC = (Word)read(0xFFFE) | ((Word)read(0xFFFF) << 8);
    return 0;
}


Byte CPU::CLC() {
    flag(CB, false);
    return 0;
}
Byte CPU::CLD() {
    flag(DM, false);
    return 0;
}
Byte CPU::CLI() {
    flag(DI, false);
    return 0;
}
Byte CPU::CLV() {
    flag(OV, false);
    return 0;
}


Byte CPU::CMP() {
    fetch();
    Word bufer = (Word)A - (Word)fetched;

    flag(CB, A >= fetched);
    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    return 1;
}
Byte CPU::CPX() {
    fetch();
    Word bufer = (Word)X - (Word)fetched;

    flag(CB, X >= fetched);
    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    return 0;
}
Byte CPU::CPY() {
    fetch();
    Word bufer = (Word)Y - (Word)fetched;

    flag(CB, Y >= fetched);
    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    return 0;
}


Byte CPU::DEC() {
    fetch();
    Word bufer = fetched-1;
    write(addressABS, bufer & 0x00FF);

    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    return 0;
}
Byte CPU::DEX() {
    X--;

    flag(ZF, X == 0x00);
    flag(NG, X & 0x80);

    return 0;
}
Byte CPU::DEY() {
    Y--;
    
    flag(ZF, Y == 0x00);
    flag(NG, Y & 0x80);

    return 0;
}


Byte CPU::EOR() {
    fetch();
    A = A ^ fetched;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 1;
}


Byte CPU::INC() {
    fetch();
    Word bufer = fetched+1;
    write(addressABS, bufer & 0x00FF);

    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    return 0;
}
Byte CPU::INX() {
    X++;

    flag(ZF, X == 0x00);
    flag(NG, X & 0x80);

    return 0;
}
Byte CPU::INY() {
    Y++;

    flag(ZF, Y == 0x00);
    flag(NG, Y & 0x80);

    return 0;
}


Byte CPU::ADC() {
    fetch();
    Word bufer = (Word)A + (Word)fetched + (Word)flag(CB);
    
    flag(CB, bufer > 255);
    flag(ZF, (bufer & 0x00FF) == 0);
    flag(NG, bufer & 0x80);
    flag(OV, (~((Word)A ^ (Word)fetched) & ((Word)A ^ (Word)bufer)) & 0x0080);

    A = bufer & 0x00FF;
    return 1;
}
Byte CPU::SBC() {
    fetch();
    Word value = ((Word)fetched) ^ 0x00FF;

    Word bufer = (Word)A + value + (Word)flag(CB);
    flag(CB, bufer & 0xFF00);
    flag(ZF, ((bufer & 0x00FF) == 0));
    flag(OV, (bufer ^ (Word)A) & (bufer ^ value) & 0x0080);
    flag(NG, bufer & 0x0080);

    A = bufer & 0x00FF;
    return 0;
}


Byte CPU::JMP() {
    PC = addressABS;
    return 0;
}
Byte CPU::JSR() {
    PC--;

    write(0x0100 + SP, (PC>>8) & 0x00FF); SP--;
    write(0x0100 + SP, PC & 0x00FF); SP--;

    PC = addressABS;
    return 0;
}


Byte CPU::LDA() {
    fetch();
    A = fetched;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 1;
}
Byte CPU::LDX() {
    fetch();
    X = fetched;

    flag(ZF, X == 0x00);
    flag(NG, X & 0x80);

    return 1;
}
Byte CPU::LDY() {
    fetch();
    Y = fetched;

    flag(ZF, Y == 0x00);
    flag(NG, Y & 0x80);

    return 1;
}
Byte CPU::LSR() {
    fetch();
    flag(CB, fetched & 0x0001);
    Word bufer = fetched >> 1;

    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    if(lookupTable[opcode].addrmode == &CPU::IMP) A = bufer & 0x00FF;
    else write(addressABS, bufer & 0x00FF);

    return 0;
}


Byte CPU::NOP() {
    switch(opcode) {
        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
        break;
    } return 0;
}


Byte CPU::ORA() {
    fetch();
    A = A | fetched;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 1;
}
Byte CPU::PHA() {
    write(0x0100 + SP, SR | BR | UN);

    flag(BR, 0);
    flag(UN, 0);
    SP--;

    return 0;
}
Byte CPU::PHP() {
    write(0x0100 + SP, SR | BR | UN);

    flag(BR, 0);
    flag(UN, 0);

    SP--;
    return 0;
}
Byte CPU::PLA() {
    SP++;
    A = read(0x0100 + SP);

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 0;
}
Byte CPU::PLP() {
    SP++;
    SR = read(0x0100 + SP);
    
    flag(UN, 1);
    return 0;
}


Byte CPU::ROL() {
    fetch();
    Word bufer = (Word)(fetched<<1) | flag(CB);

    flag(CB, bufer & 0x00FF);
    flag(ZF, (bufer & 0x00FF) == 0x0000);
    flag(NG, bufer & 0x0080);

    if(lookupTable[opcode].addrmode == &CPU::IMP) A = bufer & 0x00FF;
    else write(addressABS, bufer & 0x00FF);

    return 0;
}
Byte CPU::ROR() {
    fetch();
    Word bufer = (Word)(flag(CB)<<7) | (fetched>>1);

    flag(CB, fetched & 0x01);
    flag(ZF, (bufer & 0x00FF) == 0x00);
    flag(NG, bufer & 0x0080);

    if(lookupTable[opcode].addrmode == &CPU::IMP) A = bufer & 0x00FF;
    else write(addressABS, bufer & 0x00FF);

    return 0;
}
Byte CPU::RTI() {
    SP++;

    SR = read(0x0100 + SP);
    SR &= ~BR;
    SR &= ~UN;

    SP++; PC = (Word)read(0x0100 + SP);
    SP++; PC |= (Word)read(0x0100 + SP) << 8;

    return 0;
}
Byte CPU::RTS() {
    SP++; PC = (Word)read(0x0100 + SP);
    SP++; PC |= (Word)read(0x0100 + SP) << 8;

    PC++;
    return 0;
}


Byte CPU::SEC() {
    flag(CB, true);
    return 0;
}
Byte CPU::SED() {
    flag(DM, true);
    return 0;
}
Byte CPU::SEI() {
    flag(DI, true);
    return 0;
}

Byte CPU::STA() {
    write(addressABS, A);
    return 0;
}
Byte CPU::STX() {
    write(addressABS, X);
    return 0;
}
Byte CPU::STY() {
    write(addressABS, Y);
    return 0;
}


Byte CPU::TAX() {
    X = A;

    flag(ZF, X == 0x00);
    flag(NG, X & 0x80);

    return 0;
}
Byte CPU::TAY() {
    Y = A;

    flag(ZF, Y == 0x00);
    flag(NG, Y & 0x80);

    return 0;
}
Byte CPU::TSX() {
    X = SP;

    flag(ZF, X == 0x00);
    flag(NG, X & 0x80);

    return 0;
}
Byte CPU::TXA() {
    A = X;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 0;
}
Byte CPU::TXS() {
    SP = X;
    return 0;
}
Byte CPU::TYA() {
    A = Y;

    flag(ZF, A == 0x00);
    flag(NG, A & 0x80);

    return 0;
}


Byte CPU::XXX(){return 0;}




bool CPU::complete() {
	return cycles == 0;
}

std::map<uint16_t, std::string> CPU::disassemble(uint16_t nStart, uint16_t nStop) {
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookupTable table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->cpuRead(addr, true); addr++;
		sInst += lookupTable[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookupTable[opcode].addrmode == &CPU::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::IMM)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ZP0)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ZPX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ZPY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::IZX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::IZY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ABS)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ABX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::ABY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::IND)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookupTable[opcode].addrmode == &CPU::REL)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}