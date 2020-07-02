#include "gaia_pch.h"
#include "level.h"
#include <core/session.h>
#include <scene/scene.h>

namespace Gaia {
	bool Level::load_internal()
	{
		// Open the file
		std::ifstream file;
		file.open(m_path);
		if (!file.is_open())
		{
			GAIA_ELOG_WARN("Could not open file: " + m_path);
			return false;
		}

		// Read the data
		file >> m_data;
		return true;
	}

	bool Level::unload_internal()
	{
		m_data.clear();
		return true;
	}

	void Level::load_level(Scene* scn)const
	{
		if (!is_loaded())
			return;

		scn->deserialize(m_data);
	}

	void Level::save_level(const Scene* scn)
	{
		m_data.clear();

		scn->serialize(m_data);
		std::ofstream file(m_path);
		file << m_data;
	}

	void Level::create(const std::string & name)
	{
		auto& map = s_resources->get_map<Level>();
		auto itr = map.find(name);
		if(itr != map.end())
			return GAIA_ELOG_WARN("Resource " + name + " already exists");

		map[name] = new_shared<Level>("assets/levels/" + name + ".level", e_Extension::level, true);
		map[name]->m_data.clear();
	}
}
