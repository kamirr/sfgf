#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>

class Collider {
	std::vector<sf::Vector2f> m_arr;

public:
	void push_back(sf::Vector2f pt) {
		m_arr.push_back(pt);
	}
	void clear() {
		m_arr.clear();
	}

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


	bool intersects(Collider& poly) {
		auto arr = m_arr;
		arr.push_back(arr.front());

		auto poly_arr = poly.m_arr;
		poly_arr.push_back(poly_arr.front());

		for(auto i = 1u; i < arr.size(); ++i) {
			auto p1 = arr[i - 1], q1 = arr[i];

			for(auto j = 1u; j < poly_arr.size(); ++j) {
				auto p2 = poly_arr[j - 1], q2 = poly_arr[j];

				if(lineIntersection(p1, q1, p2, q2)) {
					return true;
				}
			}
		}

		return false;
	}
	bool contains(sf::Vector2f point) {
		int i, j, nvert = m_arr.size();
		bool c = false;

		for(i = 0, j = nvert - 1; i < nvert; j = i++) {
			auto pti = m_arr[i];
			auto ptj = m_arr[j];

			if(((pti.y >= point.y) != (ptj.y >= point.y)) &&
				(point.x <= (ptj.x - pti.x) * (point.y - pti.y) / (ptj.y - pti.y) + pti.x)) {
				c = !c;
			}
		  }

		  return c;
	}

	bool collides(Collider& poly) {
		if(intersects(poly)) {
			return true;
		}

		for(auto v: poly.m_arr) {
			if(!contains(v)) {
				return false;
			}
		}

		return true;
	}
};

#endif // COLLIDER_HPP
