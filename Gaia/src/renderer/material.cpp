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

		{
			std::string name;
			load(name, data["AlbedoTexture"]);
			m_albedo_texture = s_resources->get<Texture2D>(name);
		}
		{
			std::string name;
			load(name, data["MetallicTexture"]);
			m_metallic_texture = s_resources->get<Texture2D>(name);
		}
		{
			std::string name;
			load(name, data["RoughnessTexture"]);
			m_roughness_texture = s_resources->get<Texture2D>(name);
		}
		{
			std::string name;
			load(name, data["NormalTexture"]);
			m_normal_texture = s_resources->get<Texture2D>(name);
		}
		if (!m_albedo_texture)
			load(m_albedo_color, data["AlbedoColor"]);
		if (!m_metallic_texture)
			load(m_metallic_color, data["MetallicColor"]);
		if (!m_roughness_color)
			load(m_roughness_color, data["RoughnessColor"]);

		return true;
	}

	bool Material::unload_internal()
	{
		return true;
	}
	void Material::save_material()const
	{
		Json::Value data;

		if(m_albedo_texture)
			save(m_albedo_texture->get_name(), data["AlbedoTexture"]);
		else
			save(m_albedo_color, data["AlbedoColor"]);

		if (m_metallic_texture)
			save(m_metallic_texture->get_name(), data["MetallicTexture"]);
		else
			save(m_metallic_color, data["MetallicColor"]);

		if (m_roughness_texture)
			save(m_roughness_texture->get_name(), data["RoughnessTexture"]);
		else
			save(m_roughness_color, data["RoughnessColor"]);

		if (m_normal_texture)
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
