#ifndef OBJECTPACK_HPP
#define OBJECTPACK_HPP

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
