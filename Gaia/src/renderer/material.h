#pragma once
#include <resources/resource.h>
#include <renderer/texture2D.h>

namespace Gaia {
	class Material : public Resource
	{
	public:
		using Resource::Resource;
		Extensions(e_Extension::mtl);

		bool load_internal()override;
		bool unload_internal()override;
		void save_material()const;
		static void create(const std::string& name);

	private:
		shared<Texture2D> m_albedo_texture;
		shared<Texture2D> m_metallic_texture;
		shared<Texture2D> m_roughness_texture;
		shared<Texture2D> m_normal_texture;
		vec3 m_albedo_color = vec3(1.f, 1.f, 1.f);
		vec3 m_metallic_color = vec3(0.f, 0.f, 0.f);
		float m_roughness_color = 1.0f;
	};
}