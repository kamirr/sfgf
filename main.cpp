#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SFGF/Plane.hpp"
#include <iostream>

int main() {
	sf::Texture tx;
	tx.loadFromFile("img.png");

	sfgf::Plane p1;
	p1.setPosition({400, 300});
	p1.setSize({200, 200});
	p1.selfCenter();
	p1.setTexture(tx);

	sfgf::Polygon p2(3);
	p2.setVertices({
		{0, 0},
		{40, 16},
		{16, 40}}
	);
	p2.setTexture(tx, {
		{0, 0},
		{tx.getSize().x, 0},
		{0, tx.getSize().y}
	});

	sfgf::Plane p3;
	p3.setColor({255, 255, 255, 50});

	sf::RenderWindow app({800, 600, 32}, "app");

	sf::Clock timer;
	while(app.isOpen()) {
		auto dt = timer.restart();
		std::cout << 1 / dt.asSeconds() << std::endl;

		sfgf::GameObject::updateAll(dt);
		for(sf::Event ev; app.pollEvent(ev);) {
			if(ev.type == sf::Event::Closed) {
				app.close();
				break;
			}
		}

		app.clear({20, 20, 20});

		p1.rotate(dt.asSeconds() * 120);

		p3.setPosition({p1.getGlobalBounds().left, p1.getGlobalBounds().top});
		p3.setSize({p1.getGlobalBounds().width, p1.getGlobalBounds().height});

		p2.setPosition(app.mapPixelToCoords(sf::Mouse::getPosition(app)));
		p1.setColor(p1.collides(p2) ? sf::Color{255, 0, 0} : sf::Color{255, 255, 255});
		p3.setColor(p3.collides(p2) ? sf::Color{255, 0, 0, 50} : sf::Color{255, 255, 255, 50});

		app.draw(p1);
		app.draw(p2);
		app.draw(p3);

		app.display();
	}

	return 0;
}
