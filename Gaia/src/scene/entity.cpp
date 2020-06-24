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
	void Entity::serialize(Json::Value & json) const
	{
		save(m_name, json["Name"]);
		save(get_position(), json["Position"]);
		save(get_rotation(), json["Rotation"]);
		save(get_scale(), json["Scale"]);
		
		{
			auto& comp_json = json["Components"];
			for (auto& c : m_components)
				save(*c.second, comp_json);
		}
	}
	void Entity::deserialize(const Json::Value & json)
	{
		load(m_name, json["Name"]);
		load(get_position(), json["Position"]);
		load(get_rotation(), json["Rotation"]);
		load(get_scale(), json["Scale"]);
		m_alive = true;

		{
			auto comp_json = json["Components"];
			for (auto it = comp_json.begin(); it != comp_json.end(); ++it)
			{
				Component* cmp = ComponentFactory::get().create(it.name());
				load(*cmp, comp_json);
				cmp->m_owner = this;
				TypeInfo type = type_of(*cmp);

				m_components[type] = shared<Component>(cmp);
			}
		}
	}
}
