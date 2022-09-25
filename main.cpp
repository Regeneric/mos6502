#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "headers/Bus.hpp"
#include "headers/CPU.hpp"

#define Rectangle sf::RectangleShape
#define Circle sf::CircleShape

inline const char* const bts(bool b) {
	return b ? "true" : "false";
}

auto main(void)->int {
	std::shared_ptr<Cart> cart = std::make_shared<Cart>("nestest.nes");
	Bus bus;
		bus.insertCart(cart);
		bus.reset();

	sf::RenderWindow app;
		app.create(sf::VideoMode(680, 480, 32), "6502");
		app.setFramerateLimit(60);

	sf::Font font;
		font.loadFromFile("arial.ttf");

	sf::Text txt;
		txt.setCharacterSize(21);
		txt.setFillColor(sf::Color::Red);
		txt.setFont(font);

	int x = 10, y = 10;

	while (app.isOpen()) {
	sf::Event event;
		while (app.pollEvent(event)) {
			if (event.type == sf::Event::Closed) app.close();
		} app.clear(sf::Color(230, 230, 250));


		while(!bus.ppu.frameComplete) bus.clock();
		bus.ppu.frameComplete = false;

		txt.setString("STATUS:");
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x, y);
		app.draw(txt);

		txt.setString("N");
		txt.setFillColor(bus.cpu.SR & CPU::NG ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x, y+32);
		app.draw(txt);

		txt.setString("V");
		txt.setFillColor(bus.cpu.SR & CPU::OV ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+20, y+32);
		app.draw(txt);

		txt.setString("B");
		txt.setFillColor(bus.cpu.SR & CPU::BR ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+40, y+32);
		app.draw(txt);

		txt.setString("D");
		txt.setFillColor(bus.cpu.SR & CPU::DM ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+60, y+32);
		app.draw(txt);

		txt.setString("I");
		txt.setFillColor(bus.cpu.SR & CPU::DI ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+80, y+32);
		app.draw(txt);

		txt.setString("Z");
		txt.setFillColor(bus.cpu.SR & CPU::ZF ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+100, y+32);
		app.draw(txt);

		txt.setString("C");
		txt.setFillColor(bus.cpu.SR & CPU::CB ? sf::Color::Green : sf::Color::Red);
		txt.setPosition(x+120, y+32);
		app.draw(txt);


		txt.setString("PC: $"+std::to_string(bus.cpu.PC));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x, y+64);
		app.draw(txt);

		txt.setString("A: $"+std::to_string(bus.cpu.A));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x+80, y+64);
		app.draw(txt);

		txt.setString("X: $"+std::to_string(bus.cpu.X));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x+160, y+64);
		app.draw(txt);

		txt.setString("Y: $"+std::to_string(bus.cpu.Y));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x+240, y+64);
		app.draw(txt);

		txt.setString("SP: $"+std::to_string(bus.cpu.SP));
		txt.setFillColor(sf::Color::Black);
		txt.setPosition(x+320, y+64);
		app.draw(txt);

		app.display();
	} return 0;
}