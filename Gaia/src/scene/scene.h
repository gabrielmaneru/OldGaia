#pragma once
#include <scene/entity.h>
#include <components/camera.h>

namespace Gaia {
	class Scene :public Serializable{
	public:
		Scene(const std::string& name);
		~Scene();
		
		void enter();
		void update(float dt);
		void exit();
		Entity * create_entity(const std::string& name);
		void add_camera(const shared<Camera>& cam);
		void rem_camera(const shared<Camera>& cam);
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "Scene"; }

		const shared<Camera>& get_cam() { return m_cameras[0]; }

		static Scene* s_active_scene;

	private:
		std::string m_name;
		std::vector<Entity*> m_entities;
		std::vector<shared<Camera>> m_cameras;
	};
}