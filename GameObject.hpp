#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include "CopyLock.hpp"

namespace sfgf {
	class GameObject
		: public sf::Transformable {
	private:
		const GameObject* m_parent = nullptr;
		const CopyLock m_copyLock;

	public:
		void setParent(const GameObject& parent) {
			m_parent = &parent;
		}
		const GameObject& getParent() {
			return *m_parent;
		}

		sf::Transform getTransform() const {
			if(m_parent) {
				return m_parent->getTransform() * sf::Transformable::getTransform();
			}

			return sf::Transformable::getTransform();
		}
	};
}

#endif // GAMEOBJECT_HPP
