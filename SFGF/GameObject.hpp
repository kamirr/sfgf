#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "CopyLock.hpp"

namespace sfgf {
	class GameObject
		: public sf::Transformable {
	private:
		const GameObject* m_parent = nullptr;
		const CopyLock m_copyLock;

	public:
		virtual ~GameObject() {}

		virtual void update(sf::Time);

		void setParent(const GameObject& parent);
		const GameObject& getParent() const;

		sf::Transform getTransform() const;
	};
	void GameObject::update(sf::Time)
	{ }

	void GameObject::setParent(const GameObject& parent) {
		m_parent = &parent;
	}
	const GameObject& GameObject::getParent() const {
		return *m_parent;
	}

	sf::Transform GameObject::getTransform() const {
		if(m_parent) {
			return m_parent->getTransform() * sf::Transformable::getTransform();
		}

		return sf::Transformable::getTransform();
	}
}

#endif // GAMEOBJECT_HPP
