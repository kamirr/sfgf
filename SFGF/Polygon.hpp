#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "GameObject.hpp"
#include "Collider.hpp"

namespace sfgf {
	class Polygon
		: public GameObject
		, public sf::Drawable {
	private:
		Collider collider;
		std::vector<sf::Vertex> m_arr;
		const sf::Texture *m_tx = nullptr;

		virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
			states.transform *= getTransform();
			states.texture = m_tx;

			window.draw(m_arr.data(), 4, sf::TriangleFan, states);
		}

	public:
		Polygon(size_t size) {
			m_arr.resize(size);
			m_arr.shrink_to_fit();
		}

		void setTexture(const sf::Texture& tex, const std::vector<sf::Vector2f>& texCorrds) {
			for(auto i = 0u; i < texCorrds.size(); ++i) {
				m_arr[i].texCoords = texCorrds[i];
			}

			m_tx = &tex;
		}

		void setColor(sf::Color c) {
			for(auto& v: m_arr) {
				v.color = c;
			}
		}

		void setVertices(const std::vector<sf::Vector2f>& vertices) {
			for(auto i = 0u; i < vertices.size(); ++i) {
				m_arr[i].position = vertices[i];
			}
		}
		const std::vector<sf::Vertex>& getVertices() {
			return m_arr;
		}

		void updateCollider() {
			collider.clear();
			for(sf::Vertex& v: m_arr) {
				collider.push_back(getTransform().transformPoint(v.position));
			}
		}

		virtual void update(sf::Time) {
			updateCollider();
		}

		bool intersects(Polygon& poly) {
			return collider.intersects(poly.collider);
		}
		bool contains(sf::Vector2f point) {
			return collider.contains(point);
		}
		bool collides(Polygon& poly) {
			return collider.collides(poly.collider);
		}
	};
}

#endif // POLYGON_HPP
