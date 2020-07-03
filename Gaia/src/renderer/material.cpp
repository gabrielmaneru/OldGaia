#include "gaia_pch.h"
#include "material.h"
#include <core/session.h>

namespace Gaia {
	bool Material::load_internal()
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
		Json::Value data;
		file >> data;

		load(m_texture_active[0], data["AlbedoActive"]);
		if (m_texture_active[0])
		{
			std::string name;
			load(name, data["AlbedoTexture"]);
			m_albedo_texture = s_resources->get<Texture2D>(name);
		}
		else
			load(m_albedo_color, data["AlbedoColor"]);

		load(m_texture_active[1], data["MetallicActive"]);
		if (m_texture_active[1])
		{
			std::string name;
			load(name, data["MetallicTexture"]);
			m_metallic_texture = s_resources->get<Texture2D>(name);
		}
		else
			load(m_metallic_color, data["MetallicColor"]);

		load(m_texture_active[2], data["RoughnessActive"]);
		if (m_texture_active[2])
		{
			std::string name;
			load(name, data["RoughnessTexture"]);
			m_roughness_texture = s_resources->get<Texture2D>(name);
		}
		else
			load(m_roughness_color, data["RoughnessColor"]);

		load(m_texture_active[3], data["NormalActive"]);
		if (m_texture_active[3])
		{
			std::string name;
			load(name, data["NormalTexture"]);
			m_normal_texture = s_resources->get<Texture2D>(name);
		}

		return true;
	}

	bool Material::unload_internal()
	{
		return true;
	}
	void Material::save_material()const
	{
		Json::Value data;

		save(m_texture_active[0], data["AlbedoActive"]);
		if(m_texture_active[0])
			save(m_albedo_texture->get_name(), data["AlbedoTexture"]);
		else
			save(m_albedo_color, data["AlbedoColor"]);

		save(m_texture_active[1], data["MetallicActive"]);
		if (m_texture_active[1])
			save(m_metallic_texture->get_name(), data["MetallicTexture"]);
		else
			save(m_metallic_color, data["MetallicColor"]);

		save(m_texture_active[2], data["RoughnessActive"]);
		if (m_texture_active[2])
			save(m_roughness_texture->get_name(), data["RoughnessTexture"]);
		else
			save(m_roughness_color, data["RoughnessColor"]);

		save(m_texture_active[3], data["NormalActive"]);
		if (m_texture_active[3])
			save(m_normal_texture->get_name(), data["NormalTexture"]);

		std::ofstream file(m_path);
		file << data;
	}
	void Material::create(const std::string & name)
	{
		auto& map = s_resources->get_map<Material>();
		auto itr = map.find(name);
		if (itr != map.end())
			return GAIA_ELOG_WARN("Resource " + name + " already exists");

		map[name] = new_shared<Material>("assets/materials/" + name + ".mtl", e_Extension::mtl, true);
	}
}
