#pragma once
#include <resources/resource_manager.h>
#include <scene/scene.h>
#include <editor/editor.h>

namespace Gaia {
	class Session {
	public:
		Session();
		~Session();
		void begin();
		void update(float dt);
		void render_editor();
		void end();

		Scene* get_current_scene() { return  m_current_scene; }
		Scene* get_scene(shared<Level> lvl);
		void load_level(shared<Level> lvl);
		void remove_level(shared<Level> lvl);
		void save_level(shared<Level> lvl);

	private:
		enum class e_State { load, reload, update };
		e_State m_state{ e_State::update };
		Scene* m_current_scene{ nullptr };
		shared<Level> m_current_level;
		shared<Level> m_next_level;
		std::map<shared<Level>, Scene*> m_scenes;

		void reload();
		void load();
		void save();
	};
	extern Session* s_session;
	extern ResourceManager* s_resources;
	extern Editor* s_editor;
}