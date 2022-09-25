#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "headers/Bus.hpp"
#include "headers/CPU.hpp"

#include <chrono>
#include <unistd.h>

#define Rectangle sf::RectangleShape
#define Circle sf::CircleShape

inline const char* const bts(bool b) {
	return b ? "true" : "false";
}

std::string hex(uint32_t n, uint8_t d) {
	std::string s(d, '0');
	for(int i = d-1; i >= 0; i--, n >>= 4)
		s[i] = "0123456789ABCDEF"[n & 0xF];
	return s;
};

auto main(void)->int {
	std::shared_ptr<Cart> cart = std::make_shared<Cart>("nestest.nes");
	Bus bus;
		bus.insertCart(cart);
		bus.reset();

	sf::RenderWindow app;
		app.create(sf::VideoMode(680, 480, 32), "6502");
		app.setFramerateLimit(5000);

	sf::Font font;
		font.loadFromFile("arial.ttf");

	sf::Text txt;
		txt.setCharacterSize(21);
		txt.setFillColor(sf::Color::Red);
		txt.setFont(font);

	int x = 10, y = 10;

	while(app.isOpen()) {
	sf::Event event;
		while(app.pollEvent(event)) {
			if(event.type == sf::Event::Closed) app.close();
		} app.clear(sf::Color(230, 230, 250));

		while(!bus.ppu.frameComplete) bus.clock();
		bus.ppu.frameComplete = false;

		auto size = bus.ppu.screen().size();
		app.draw(&bus.ppu.screen()[0], bus.ppu.screen().size(), sf::Quads);
		// for(const auto &s : bus.ppu.screen()) app.draw(s);
		bus.ppu.screen().resize(0);

		// txt.setString("STATUS:");
		// txt.setFillColor(sf::Color::Black);
		// txt.setPosition(x, y);
		// app.draw(txt);

		// txt.setString("N");
		// txt.setFillColor(bus.cpu.SR & CPU::NG ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x, y+32);
		// app.draw(txt);

		// txt.setString("V");
		// txt.setFillColor(bus.cpu.SR & CPU::OV ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+20, y+32);
		// app.draw(txt);

		// txt.setString("B");
		// txt.setFillColor(bus.cpu.SR & CPU::BR ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+40, y+32);
		// app.draw(txt);

		// txt.setString("D");
		// txt.setFillColor(bus.cpu.SR & CPU::DM ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+60, y+32);
		// app.draw(txt);

		// txt.setString("I");
		// txt.setFillColor(bus.cpu.SR & CPU::DI ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+80, y+32);
		// app.draw(txt);

		// txt.setString("Z");
		// txt.setFillColor(bus.cpu.SR & CPU::ZF ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+100, y+32);
		// app.draw(txt);

		// txt.setString("C");
		// txt.setFillColor(bus.cpu.SR & CPU::CB ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+120, y+32);
		// app.draw(txt);

		// txt.setString("-");
		// txt.setFillColor(bus.cpu.SR & CPU::UN ? sf::Color::Green : sf::Color::Red);
		// txt.setPosition(x+140, y+32);
		// app.draw(txt);


		// txt.setString("PC: $" + hex(bus.cpu.PC, 4));
		// txt.setFillColor(sf::Color::Black);
		// txt.setPosition(x, y+64);
		// app.draw(txt);

		// txt.setString("A: $" + hex(bus.cpu.A, 2));
		// txt.setFillColor(sf::Color::Black);
		// txt.setPosition(x+120, y+64);
		// app.draw(txt);

		// txt.setString("X: $" + hex(bus.cpu.X, 2));
		// txt.setFillColor(sf::Color::Black);
		// txt.setPosition(x+240, y+64);
		// app.draw(txt);

		// txt.setString("Y: $" + hex(bus.cpu.Y, 2));
		// txt.setFillColor(sf::Color::Black);
		// txt.setPosition(x+360, y+64);
		// app.draw(txt);

		txt.setString("SP: $" + hex(bus.cpu.SP, 4));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x+480, y+64);
		app.draw(txt);

		// txt.setString(bts(bus.ppu.frameComplete));
		// txt.setFillColor(sf::Color::Red);
		// txt.setPosition(x, y+96);
		// app.draw(txt);

		app.display();
	} return 0;
}