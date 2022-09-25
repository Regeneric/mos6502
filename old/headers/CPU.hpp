#pragma once

#include <cstdint>
#include <cstdio>

#include <string>
#include <vector>
#include <map>

using Word = uint16_t;
using Byte = uint8_t;

class Bus;
class CPU {

public:
    CPU();
    ~CPU();

    // Flags of Status Register
    enum FLAGS {
        CB = (1<<0),    // Carry Bit
        ZF = (1<<1),    // Zero Flag
        DI = (1<<2),    // Disable Interrputs
        DM = (1<<3),    // Decimal Mode
        BR = (1<<4),    // Break
        UN = (1<<5),    // Unused
        OV = (1<<6),    // Overflow
        NG = (1<<7),    // Negative
    };

    Byte A = 0x00;      // Accumulator
    Byte X = 0x00;      // X Register
    Byte Y = 0x00;      // Y Register

    Byte SP = 0x00;     // Stack Pointer
    Byte SR = 0x00;     // Status Register
    Word PC = 0x0000;   // Program Counter


    std::map<Word, std::string> disassemble(Word nStart, Word nStop);

    void busConnector(Bus *b){bus = b;}

    void clock();
    void reset();
    void irq();
    void nmi();

    bool complete();

private:
    Byte fetched = 0x00;

    Word addressABS = 0x0000;
    Word addressREL = 0x00;
    
    Byte opcode = 0x00;
    Byte cycles = 0;
    
    Bus *bus = nullptr;

    Byte fetch();

    void write(Word address, Byte data);
    Byte read(Word address);  

    void flag(FLAGS flag, bool status);
    Byte flag(FLAGS flag);


    struct INSTRUCTIONS {
        std::string name;
        Byte (CPU::*operate)(void) = nullptr;
        Byte (CPU::*addrmode)(void) = nullptr;
        Byte cycles = 0;
    }; std::vector<INSTRUCTIONS> lookupTable;


    // Addressing Modes
    Byte IZY(); Byte IMP();
    Byte IND(); Byte ZP0();
    Byte ABX(); Byte ZPY();
    Byte REL(); Byte ABS();
    Byte ZPX(); Byte ABY();
    Byte IMM(); Byte IZX();


    // Opcodes
	Byte ADC();	Byte AND();	Byte ASL();	Byte BCC();
	Byte BCS();	Byte BEQ();	Byte BIT();	Byte BMI();
	Byte BNE();	Byte BPL();	Byte BRK();	Byte BVC();
	Byte BVS();	Byte CLC();	Byte CLD();	Byte CLI();
	Byte CLV();	Byte CMP();	Byte CPX();	Byte CPY();
	Byte DEC();	Byte DEX();	Byte DEY();	Byte EOR();
	Byte INC();	Byte INX();	Byte INY();	Byte JMP();
	Byte JSR();	Byte LDA();	Byte LDX();	Byte LDY();
	Byte LSR();	Byte NOP();	Byte ORA();	Byte PHA();
	Byte PHP();	Byte PLA();	Byte PLP();	Byte ROL();
	Byte ROR();	Byte RTI();	Byte RTS();	Byte SBC();
	Byte SEC();	Byte SED();	Byte SEI();	Byte STA();
	Byte STX();	Byte STY();	Byte TAX();	Byte TAY();
	Byte TSX();	Byte TXA();	Byte TXS();	Byte TYA();

    // Catch unidentified opcodes
    Byte XXX();
};