#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SFGF/ObjectPack.hpp"
#include "SFGF/Plane.hpp"
#include <iostream>
#include <random>
#include <memory>

struct Rect {
	std::shared_ptr<sfgf::Plane> plane;
	sf::Vector2f unit;

	Rect(std::default_random_engine& en) {
		plane = std::make_shared<sfgf::Plane>();
		sfgf::Plane& obj = *plane;

		std::uniform_real_distribution<float> left(0, 780);
		std::uniform_real_distribution<float> top(0, 580);

		obj.setPosition({left(en), top(en)});
		obj.setSize({20, 20});

		std::uniform_real_distribution<float> up(-3, 3);
		std::uniform_int_distribution<int> dir(0, 1);
		unit.y = up(en);
		unit.x = std::sqrt(9 - unit.y * unit.y) * (dir(en) * 2 - 1);
	}

	void move() {
		plane->move(unit);
		auto pos = plane->getPosition();
		if(pos.x < 0 || pos.x > 780) {
			unit.x *= -1;
		}
		if(pos.y < 0 || pos.y > 580) {
			unit.y *= -1;
		}
	}
};

int main() {
	sf::RenderWindow app({800, 600, 32}, "app");

	std::default_random_engine en{std::random_device{}()};

	std::vector<Rect> rectangles;
	sfgf::ObjectPack pack;

	for(auto i = 0u; i < 500; ++i) {
		rectangles.emplace_back(en);
		pack.add(*rectangles.back().plane);
	}

	sf::Clock timer;
	while(app.isOpen()) {
		auto dt = timer.restart();
		std::cout << 1 / dt.asSeconds() << std::endl;

		pack.update(dt);
		for(sf::Event ev; app.pollEvent(ev);) {
			if(ev.type == sf::Event::Closed) {
				app.close();
				break;
			}
		}

		app.clear({20, 20, 20});

		for(auto i = 0u; i < rectangles.size(); ++i) {
			auto& obj1 = *rectangles[i].plane;

			for(auto j = i + 1; j < rectangles.size(); ++j) {
				auto& obj2 = *rectangles[j].plane;

				if(obj1.collides(obj2)) {
					obj1.setColor(sf::Color{230, 20, 20, 30});
					obj2.setColor(sf::Color{230, 20, 20, 30});
				}
			}

			app.draw(obj1);
			obj1.setColor(sf::Color{230, 230, 230, 30});
			rectangles[i].move();

		}

		app.display();
	}

	return 0;
}
