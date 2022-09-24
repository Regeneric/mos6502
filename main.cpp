#include <iostream>
#include <sstream>

#include "headers/Bus.hpp"
#include "headers/CPU.hpp"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



class DEMO_CPU : public olc::PixelGameEngine
{
public:
	DEMO_CPU() { sAppName = "DEMOC CPU"; }

	Bus bus;
	std::map<uint16_t, std::string> mapAsm;

	std::string hex(uint32_t n, uint8_t d) {
		std::string s(d, '0');
		for(int i = d-1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns) {
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++) {
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for(int col = 0; col < nColumns; col++) {
				sOffset += " " + hex(bus.read(nAddr, true), 2);
				nAddr += 1;
			}

			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y) {
		std::string status = "STATUS: ";
		DrawString(x , y , "STATUS:", olc::WHITE);
		DrawString(x  + 64, y, "N", bus.cpu.SR & CPU::NG ? olc::GREEN : olc::RED);
		DrawString(x  + 80, y , "V", bus.cpu.SR & CPU::OV ? olc::GREEN : olc::RED);
		DrawString(x  + 96, y , "-", bus.cpu.SR & CPU::UN ? olc::GREEN : olc::RED);
		DrawString(x  + 112, y , "B", bus.cpu.SR & CPU::BR ? olc::GREEN : olc::RED);
		DrawString(x  + 128, y , "D", bus.cpu.SR & CPU::DM ? olc::GREEN : olc::RED);
		DrawString(x  + 144, y , "I", bus.cpu.SR & CPU::DI ? olc::GREEN : olc::RED);
		DrawString(x  + 160, y , "Z", bus.cpu.SR & CPU::ZF ? olc::GREEN : olc::RED);
		DrawString(x  + 178, y , "C", bus.cpu.SR & CPU::CB ? olc::GREEN : olc::RED);
		DrawString(x , y + 10, "PC: $" + hex(bus.cpu.PC, 4));
		DrawString(x , y + 20, "A: $" +  hex(bus.cpu.A, 2) + "  [" + std::to_string(bus.cpu.A) + "]");
		DrawString(x , y + 30, "X: $" +  hex(bus.cpu.X, 2) + "  [" + std::to_string(bus.cpu.X) + "]");
		DrawString(x , y + 40, "Y: $" +  hex(bus.cpu.Y, 2) + "  [" + std::to_string(bus.cpu.Y) + "]");
		DrawString(x , y + 50, "Stack P: $" + hex(bus.cpu.SP, 4));
	}

	void DrawCode(int x, int y, int nLines) {
		auto it_a = mapAsm.find(bus.cpu.PC);
		int nLineY = (nLines >> 1) * 10 + y;
		if(it_a != mapAsm.end()) {
			DrawString(x, nLineY, (*it_a).second, olc::CYAN);
			while(nLineY < (nLines * 10) + y) {
				nLineY += 10;
				if (++it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}

		it_a = mapAsm.find(bus.cpu.PC);
		nLineY = (nLines >> 1) * 10 + y;
		if(it_a != mapAsm.end()) {
			while(nLineY > y) {
				nLineY -= 10;
				if (--it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}
	}

	bool OnUserCreate() {
		/*
			*=$8000
			LDX #3
			STX $0000
			LDX #5
			STX $0001
			LDY $0000
			LDA #0
			CLC
			loop
			ADC $0001
			DEY
			BNE loop
			STA $0002
			NOP
			NOP
			NOP
		*/
		
		// Convert hex string into bytes for RAM
		std::stringstream ss;
		ss << "A2 03 8E 00 00 A2 05 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
		// ss << "4C 69 69 4C 00 80 A2 03 8E 00 00 A2 05 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
        uint16_t nOffset = 0x8000;
		while(!ss.eof()) {
			std::string b;
			ss >> b;
			bus.RAM[nOffset++] = (uint8_t)std::stoul(b, nullptr, 16);
		}

		// Set Reset Vector
		bus.RAM[0xFFFC] = 0x00;
		bus.RAM[0xFFFD] = 0x80;
				
		// Extract dissassembly
		mapAsm = bus.cpu.disassemble(0x0000, 0xFFFF);

		// Reset
		bus.cpu.reset();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		Clear(olc::DARK_RED);

		if(GetKey(olc::Key::SPACE).bPressed) {
			do {bus.cpu.clock();}
			while(!bus.cpu.complete());
		}

		if(GetKey(olc::Key::R).bPressed) bus.cpu.reset();
		if (GetKey(olc::Key::I).bPressed) bus.cpu.irq();
		if (GetKey(olc::Key::N).bPressed) bus.cpu.nmi();

		// Draw Ram Page 0x00		
		DrawRam(2, 2, 0x0000, 16, 16);
		DrawRam(2, 182, 0x8000, 16, 16);
		DrawCpu(448, 2);
		DrawCode(448, 72, 26);

		DrawString(10, 370, "SPACE = Step Instruction    R = RESET    I = IRQ    N = NMI");

		return true;
	}
};


int main() {
	DEMO_CPU demo;
	demo.Construct(680, 480, 2, 2);
	demo.Start();
    
	return 0;
}