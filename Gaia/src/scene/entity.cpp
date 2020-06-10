#include "gaia_pch.h"
#include "entity.h"
namespace Gaia {
	Entity::Entity(const std::string & name)
		: m_alive(true), m_name(name), m_transform({ 1.f }) {}

	void Entity::destoy()
	{
		m_alive = false;
	}
}
