#ifndef OBJECTPACK_HPP
#define OBJECTPACK_HPP

/* =========================================================== *
 * SFGF (c) Kamil Koczurek | koczurekk@gmail.com               *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

#include "GameObject.hpp"
#include <vector>

namespace sfgf {
	class ObjectPack {
		std::vector<GameObject*> m_objects;

	public:
		template<class ... args_t>
		ObjectPack(args_t& ... list) {
			m_objects = {&list ...};
		}

		void add(GameObject& obj) {
			m_objects.push_back(&obj);
		}
		void remove(GameObject& obj) {
			std::remove(m_objects.begin(), m_objects.end(), &obj);
		}

		void update(sf::Time t) {
			for(auto& ptr: m_objects) {
				ptr->update(t);
			}
		}
	};
}

#endif // OBJECTPACK_HPP
