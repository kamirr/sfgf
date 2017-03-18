#ifndef PLANE_HPP
#define PLANE_HPP

#include <SFML/Graphics/Texture.hpp>
#include "Polygon.hpp"

namespace sfgf {
	class Plane
		: public Polygon {
	public:
		Plane()
			: Polygon(4)
		{}

		void setTexture(const sf::Texture& tex) {
			Polygon::setTexture(tex, {
				{0.f, 0.f},
				{static_cast<float>(tex.getSize().x), 0.f},
				static_cast<sf::Vector2f>(tex.getSize()),
				{0.f, static_cast<float>(tex.getSize().y)}
			});
		}

		void setSize(sf::Vector2f size) {
			setVertices({
				{0, 0},
				{size.x, 0},
				size,
				{0, size.y}
			});
		}
		sf::Vector2f getSize() {
			return getVertices()[2].position;
		}
		void selfCenter() {
			setOrigin(getSize() / 2.f);
		}
	};
}

#endif // PLANE_HPP
