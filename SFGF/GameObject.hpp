#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

/* =========================================================== *
 * SFGF (c) Kamil Koczurek | koczurekk@gmail.com               *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "CopyLock.hpp"

namespace sfgf {
	//! \brief Base class for game objects
	//!
	//! Inherits sf::Transformable and supports child–parent relation. <br />
	//! Can be used to write custom entities compatible with sfgf API:
	//! \code{.cpp}
	//! class MahObject
	//!	: public sfgf::GameObject {
	//!		virtual void update(sf::Time t) {
	//!			std::cout << "FPS: " << 1.f / t.asSeconds() << std::endl;
	//!		}
	//! }
	//! \endcode
	//!
	//! Instances of sfgf::GameObject are not copyable due to usage of sfgf::CopyLock.
	class GameObject
		: public sf::Transformable {
	private:
		const GameObject* m_parent = nullptr;
		const CopyLock m_copyLock;

	public:
		virtual ~GameObject() {}

		//! \brief Meant to be called every frame
		//!
		//! \param [in] dt – Delta time between (logical) frames
		//!
		//! Virtual function makes it easier to pack objects into sfgf::ObjectPack and enables them to be updated together.
		//! Should be overwritten in new entity that changes its behavior based on time passing by.
		virtual void update(sf::Time dt);

		//! \brief Sets parent
		//!
		//! \param [in] parent – sfgf::GameObject to be used as parent
		//!
		//! All transformations are applied as if parent coordinates were center of coordinate system and it was rotated by its angle etc. <br />
		//! Long story short: Works same way as any parent–children hierarchy in any decent engine
		//! (i.e. <a href="https://unity3d.com/">Unity</a>, <a href="https://www.unrealengine.com/what-is-unreal-engine-4">Unreal</a>).
		void setParent(const GameObject& parent);

		//! \brief Access parent
		//! \returns Const reference to parent
		const GameObject& getParent() const;

		//! \brief Access transform
		//! \returns Internal transform multiplied by parent's transform (or not if there's no parent set).
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
