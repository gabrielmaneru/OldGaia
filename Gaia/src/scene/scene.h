#pragma once
#include <scene/entity.h>
#include <components/camera.h>
#include <scene/level.h>

namespace Gaia {
	class Scene :public Serializable{
	public:
		~Scene();
		
		void load_level(shared<Level> lvl);
		void save_level(shared<Level> lvl);
		void enter();
		void update(float dt);
		void exit();
		void clear();

		Entity * create_entity(const std::string& name);
		void add_camera(const shared<Camera>& cam);
		void rem_camera(const shared<Camera>& cam);
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "Scene"; }

		const shared<Camera>& get_cam() { return m_cameras[0]; }
		
	private:
		shared<Level> m_level;
		std::string m_name;
		std::vector<Entity*> m_entities;
		std::vector<shared<Camera>> m_cameras;
	};
}