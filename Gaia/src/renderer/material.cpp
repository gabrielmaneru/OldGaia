#include "gaia_pch.h"
#include "material.h"
#include <core/session.h>
#include <renderer/shader.h>

#include <Glad/glad.h>

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
	void Material::set_material(Shader * shader)
	{
		shader->set_uniform("active_albedo_txt", m_texture_active[0]);
		if (m_texture_active[0] && m_albedo_texture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_albedo_texture->get_id());
		}
		else
			shader->set_uniform("albedo_color", m_albedo_color);

		shader->set_uniform("active_metallic_txt", m_texture_active[1]);
		if (m_texture_active[1] && m_metallic_texture)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_metallic_texture->get_id());
		}
		else
			shader->set_uniform("metallic_value", m_metallic_color);

		shader->set_uniform("active_roughness_txt", m_texture_active[2]);
		if (m_texture_active[2] && m_roughness_texture)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_roughness_texture->get_id());
		}
		else
			shader->set_uniform("roughness_value", m_roughness_color);

		shader->set_uniform("active_normal_txt", m_texture_active[3]);
		if (m_texture_active[3] && m_normal_texture)
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, m_normal_texture->get_id());
		}

	}
	void Material::set_def_material(Shader * shader)
	{
		s_resources->get<Material>("error")->set_material(shader);
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
