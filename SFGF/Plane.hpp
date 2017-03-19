#ifndef PLANE_HPP
#define PLANE_HPP

#include <SFML/Graphics/Texture.hpp>
#include "Polygon.hpp"

namespace sfgf {
	class Plane
		: public Polygon {
	public:
		Plane();

		void setTexture(const sf::Texture& tex);

		void setSize(sf::Vector2f size);
		sf::Vector2f getSize() const;
		void selfCenter();
	};

	Plane::Plane()
		: Polygon(4)
	{}

	void Plane::setTexture(const sf::Texture& tex) {
		Polygon::setTexture(tex, {
			{0.f, 0.f},
			{static_cast<float>(tex.getSize().x), 0.f},
			static_cast<sf::Vector2f>(tex.getSize()),
			{0.f, static_cast<float>(tex.getSize().y)}
		});
	}

	void Plane::setSize(sf::Vector2f size) {
		setVertices({
			{0, 0},
			{size.x, 0},
			size,
			{0, size.y}
		});
	}
	sf::Vector2f Plane::getSize() const {
		return getVertices()[2].position;
	}
	void Plane::selfCenter() {
		setOrigin(getSize() / 2.f);
	}
}

#endif // PLANE_HPP
