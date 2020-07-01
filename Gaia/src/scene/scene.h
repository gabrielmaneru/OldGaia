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
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "Scene"; }

		shared<Camera> m_editor_camera;
		shared<Camera> m_game_camera;
		
		friend class Editor;
		friend class Entity;
	private:
		Entity* m_selected{nullptr};
		shared<Level> m_level;
		std::string m_name;
		std::vector<Entity*> m_entities;
	};
}