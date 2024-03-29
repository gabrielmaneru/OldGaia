#pragma once
#include <resources/resource.h>
#include <renderer/texture2D.h>

namespace Gaia {
	class Shader;
	class Material : public Resource
	{
	public:
		using Resource::Resource;
		Extensions(e_Extension::mtl);

		bool load_internal()override;
		bool unload_internal()override;
		void save_material()const;
		void set_material(Shader* shader);
		static void set_def_material(Shader* shader);
		static void create(const std::string& name);

		bool m_texture_active[4]{false};

		shared<Texture2D> m_albedo_texture;
		shared<Texture2D> m_metallic_texture;
		shared<Texture2D> m_roughness_texture;
		shared<Texture2D> m_normal_texture;

		vec3 m_albedo_color = vec3(1.f, 1.f, 1.f);
		float m_metallic_color = 0.0f;
		float m_roughness_color = 1.0f;
	};
}