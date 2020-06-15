#pragma once
#include <scene/entity.h>
#include <components/camera.h>

namespace Gaia {
	class Scene {
	public:
		Scene(const std::string& name);
		~Scene();
		
		void update(float dt);
		Entity * create_entity(const std::string& name);
		void add_camera(const shared<Camera>& cam);
		void rem_camera(const shared<Camera>& cam);

		const shared<Camera>& get_cam() { return m_cameras[0]; }

		static Scene* s_active_scene;

	private:
		std::string m_name;
		std::vector<Entity*> m_entities;
		std::vector<shared<Camera>> m_cameras;
	};
}