#include "gaia_pch.h"
#include "entity.h"

namespace Gaia {
	Entity::Entity(const std::string & name)
		: m_alive(true), m_name(name) {}

	void Entity::enter()
	{
		for (auto& c : m_components)
			c.second->enter();
	}

	void Entity::update(float dt)
	{
		if (m_alive)
			for (auto& c : m_components)
				c.second->update(dt);
	}

	void Entity::exit()
	{
		if (m_alive)
		{
			for (auto& c : m_components)
				c.second->exit();
			m_alive = false;
		}
		else
			GAIA_ELOG_WARN("Destroying object {0} twice", m_name);
	}
}
