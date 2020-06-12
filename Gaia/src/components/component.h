#pragma once

namespace Gaia {
	class Entity;

	class Component{
	public:
		Component(Entity* ow=nullptr)
			:m_owner(ow) {}
		virtual ~Component() = default;
		virtual void initialize() {}
		virtual void enter() {}
		virtual void update(float dt) {}
		virtual void exit() {}

		Entity* get_owner()const { return m_owner; }

	protected:
		Entity* m_owner;
	};
}