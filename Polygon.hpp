#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "GameObject.hpp"

class Polygon
	: public GameObject
	, public sf::Drawable {
private:
	std::vector<sf::Vertex> m_arr;
	const sf::Texture *m_tx = nullptr;

	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		states.transform *= getTransform();
		states.texture = m_tx;

		window.draw(m_arr.data(), 4, sf::TriangleFan, states);
	}

protected:
	static bool lineIntersection(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2) {
		auto isOnSegment = [](sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
			return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
					q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
		};
		auto orientation = [](sf::Vector2f p, sf::Vector2f q, sf::Vector2f r) {
			int val = (q.y - p.y) * (r.x - q.x) -
					  (q.x - p.x) * (r.y - q.y);

			if (val == 0) {
				return 0;
			}

			return (val > 0) ? 1 : 2;
		};

		// Find the four orientations needed for general and
		// special cases
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		// General case
		if (o1 != o2 && o3 != o4)
			return true;

		// Special Cases
		if ((o1 == 0 && isOnSegment(p1, p2, q1))
		||  (o2 == 0 && isOnSegment(p1, q2, q1))
		||  (o3 == 0 && isOnSegment(p2, p1, q2))
		||  (o4 == 0 && isOnSegment(p2, q1, q2))) {
			return true;
		}

		return false;
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

	bool intersects(Polygon& poly) {
		auto arr = getVertices();
		arr.push_back(arr.front());

		auto poly_arr = poly.getVertices();
		poly_arr.push_back(poly_arr.front());

		auto transform = getTransform();
		auto poly_transform = poly.getTransform();

		for(auto i = 1u; i < arr.size(); ++i) {
			auto p1 = arr[i - 1].position, q1 = arr[i].position;
			p1 = transform * p1;
			q1 = transform * q1;

			for(auto j = 1u; j < poly_arr.size(); ++j) {
				auto p2 = poly_arr[j - 1].position, q2 = poly_arr[j].position;
				p2 = poly_transform * p2;
				q2 = poly_transform * q2;

				if(lineIntersection(p1, q1, p2, q2)) {
					return true;
				}
			}
		}

		return false;
	}
	bool contains(sf::Vector2f point) {
		auto transform = getTransform();
		int i, j, nvert = m_arr.size();
		bool c = false;

		for(i = 0, j = nvert - 1; i < nvert; j = i++) {
			auto pti = transform.transformPoint(m_arr[i].position);
			auto ptj = transform.transformPoint(m_arr[j].position);

			if(((pti.y >= point.y) != (ptj.y >= point.y)) &&
				(point.x <= (ptj.x - pti.x) * (point.y - pti.y) / (ptj.y - pti.y) + pti.x)) {
				c = !c;
			}
		  }

		  return c;
	}

	bool collides(Polygon& poly) {
		if(intersects(poly)) {
			return true;
		}

		for(auto v: poly.getVertices()) {
			auto crd = poly.getTransform().transformPoint(v.position);

			if(!contains(crd)) {
				return false;
			}
		}

		return true;
	}
};

#endif // POLYGON_HPP
