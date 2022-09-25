#include <iostream>
#include <sstream>

#include "headers/Bus.hpp"
#include "headers/CPU.hpp"
#include "headers/PPU.hpp"
#include "headers/Cart.hpp"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



class DEMO_CPU : public olc::PixelGameEngine
{
public:
	DEMO_CPU() { sAppName = "DEMOC CPU"; }

	std::shared_ptr<Cart> cart;
	Bus bus;
	std::map<uint16_t, std::string> mapAsm;

	bool emulationRun = false;
	float residualTime = 0.0f;

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
				sOffset += " " + hex(bus.cpuRead(nAddr, true), 2);
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
		cart = std::make_shared<Cart>("nestest.nes");
		bus.insertCart(cart);

		mapAsm = bus.cpu.disassemble(0x000, 0xFFFF);
		bus.reset();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) {
		Clear(olc::DARK_RED);
		if(emulationRun) {
			if(residualTime > 0.0f) residualTime -= fElapsedTime;
			else {
				residualTime += (1.0f / 60.0f) - fElapsedTime;
				do {bus.clock();} while (!bus.ppu.frame_complete);
				bus.ppu.frame_complete = false;
			}
		} else {
			// Emulate code step-by-step
			if(GetKey(olc::Key::C).bPressed) {
				// Clock enough times to execute a whole CPU instruction
				do {bus.clock();} while (!bus.cpu.complete());
				// CPU clock runs slower than system clock, so it may be
				// complete for additional system clock cycles. Drain
				// those out
				do {bus.clock();} while (bus.cpu.complete());
			}

			// Emulate one whole frame
			if (GetKey(olc::Key::F).bPressed)
			{
				// Clock enough times to draw a single frame
				do { bus.clock(); } while (!bus.ppu.frame_complete);
				// Use residual clock cycles to complete current instruction
				do { bus.clock(); } while (!bus.cpu.complete());
				// Reset frame completion flag
				bus.ppu.frame_complete = false;
			}
		}


		if (GetKey(olc::Key::SPACE).bPressed) emulationRun = !emulationRun;
		if (GetKey(olc::Key::R).bPressed) bus.reset();		

		DrawCpu(516, 2);
		DrawCode(516, 72, 26);

		DrawSprite(0, 0, &bus.ppu.GetScreen(), 2);

		return true;
	}
};


int main() {
	DEMO_CPU demo;
	demo.Construct(680, 480, 2, 2);
	demo.Start();
    
	return 0;
}