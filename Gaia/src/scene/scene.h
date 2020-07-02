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
		shared<Level> get_level() { return m_level; }
		std::vector<Entity*>& get_entities() { return m_entities; }

		shared<Camera> m_editor_camera;
		shared<Camera> m_game_camera;
		Entity* m_selected{nullptr};
		
		friend class Entity;
	private:
		shared<Level> m_level;
		std::vector<Entity*> m_entities;
	};
}