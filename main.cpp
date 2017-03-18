#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SFGF/Plane.hpp"
#include <iostream>

int main() {
	sfgf::Plane p1;
	p1.setPosition({400, 300});
	p1.setSize({200, 200});
	p1.selfCenter();

	sf::Texture tx;
	tx.loadFromFile("img.png");
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

	sf::RenderWindow app({800, 600, 32}, "app");
	app.setFramerateLimit(60);

	while(app.isOpen()) {
		for(sf::Event ev; app.pollEvent(ev);) {
			if(ev.type == sf::Event::Closed) {
				app.close();
				break;
			}
		}

		app.clear({20, 20, 20});

		p2.setPosition(app.mapPixelToCoords(sf::Mouse::getPosition(app)));
		p2.setColor(p1.collides(p2) ? sf::Color{255, 0, 0} : sf::Color{255, 255, 255});

		app.draw(p1);
		app.draw(p2);

		app.display();
	}

	return 0;
}
