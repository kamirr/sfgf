#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Plane.hpp"
#include <iostream>

int main() {
	Plane p1;
	p1.setPosition({400, 300});
	p1.setSize({200, 200});
	p1.selfCenter();

	Plane p2;
	p2.setSize({50, 50});
	p2.setRotation(45);
	p2.selfCenter();

	sf::Texture tx;
	tx.loadFromFile("img.png");
	p1.setTexture(tx);
	p2.setTexture(tx);

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
		std::cout << p1.collides(p2) << std::endl;

		app.draw(p1);
		app.draw(p2);

		app.display();
	}

	return 0;
}
