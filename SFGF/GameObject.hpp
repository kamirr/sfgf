#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "CopyLock.hpp"
#include <vector>

namespace sfgf {
	class GameObject
		: public sf::Transformable {
	private:
		static std::vector<GameObject*>& getObjects() {
			static std::vector<GameObject*> v;
			return v;
		}

		const GameObject* m_parent = nullptr;
		const CopyLock m_copyLock;

	public:
		GameObject();
		virtual ~GameObject();

		static void updateAll(sf::Time t);
		virtual void update(sf::Time);

		void setParent(const GameObject& parent);
		const GameObject& getParent() const;

		sf::Transform getTransform() const;
	};

	GameObject::GameObject() {
		getObjects().push_back(this);
	}
	GameObject::~GameObject() {
		auto& v = getObjects();
		v.erase(std::remove(v.begin(), v.end(), this), v.end());
	}

	void GameObject::updateAll(sf::Time t) {
		for(auto ptr: getObjects()) {
			ptr->update(t);
		}
	}
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
