#pragma once
#include <scene/entity.h>

namespace Gaia {
	class Scene {
	public:
		Scene(const std::string& name);
		~Scene();

		Entity * create_entity(const std::string& name);

	private:
		std::string m_name;
		std::vector<Entity*> m_entities;
	};
}