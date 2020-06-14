#pragma once
#include <scene/entity.h>
#include <components/camera.h>

namespace Gaia {
	class Scene {
	public:
		Scene(const std::string& name);
		~Scene();


		Entity * create_entity(const std::string& name);
		void add_camera(const shared<Camera>& cam);
		void rem_camera(const shared<Camera>& cam);

		static Scene* s_active_scene;

	private:
		std::string m_name;
		std::vector<Entity*> m_entities;
		std::vector<shared<Camera>> m_cameras;
	};
}