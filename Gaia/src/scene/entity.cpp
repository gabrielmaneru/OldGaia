#include "gaia_pch.h"
#include "entity.h"

namespace Gaia {
	Entity::Entity(const std::string & name)
		: m_alive(true), m_name(name), m_transform({ 1.f }) {}

	void Entity::destroy()
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
