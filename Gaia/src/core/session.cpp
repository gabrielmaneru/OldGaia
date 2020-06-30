#include "gaia_pch.h"
#include "session.h"
#include <core/engine.h>

namespace Gaia {
	Session* s_session = nullptr;
	ResourceManager* s_resources = nullptr;
	Editor* s_editor = nullptr;
	Session::Session()
	{
		s_session = this;
		m_current_scene = new Scene();
		m_current_level = nullptr;
		m_next_level = nullptr;

		s_resources = new ResourceManager();
		s_editor = new Editor();
	}
	Session::~Session()
	{
		delete s_editor;
		delete s_resources;
		s_session = nullptr;
	}
	void Session::begin()
	{
		if (m_state == e_State::load)
			load();
			 
		m_current_scene->enter();
		m_state = e_State::update;
	}

	void Session::update(float dt)
	{
		if (m_current_scene)
		{
			if (m_state == e_State::load)
				load();
			else if(m_state == e_State::reload)
				reload();

			m_current_scene->update(dt);
		}
	}

	void Session::render_editor()
	{
		s_editor->render();
	}

	void Session::end()
	{
		save();

		// If Current scene is not linked / Dummy
		if (!m_current_level && m_current_scene)
		{
			m_current_scene->exit();
			m_current_scene->clear();

			delete m_current_scene;
			m_current_scene = nullptr;
		}
		for (auto& scn : m_scenes)
		{
			m_current_scene = scn.second;
			m_current_scene->clear();
			m_current_scene->exit();
			delete m_current_scene;
		}
		m_scenes.clear();
		m_current_scene = nullptr;
		m_current_level = nullptr;
		m_next_level = nullptr;
	}
	Scene * Session::get_scene(shared<Level> lvl)
	{
		auto it = m_scenes.find(lvl);
		if (it == m_scenes.end())
			return nullptr;
		
		return it->second;
	}
	void Session::load_level(shared<Level> lvl)
	{
		if (!lvl)
			return GAIA_ELOG_WARN("Trying to load an unexisting level");

		m_state = e_State::load;
		m_next_level = lvl;
	}
	void Session::remove_level(shared<Level> lvl)
	{
		auto scn = get_scene(lvl);
		if (!scn)
			return GAIA_ELOG_WARN("Invalid scene");
		if(scn == m_current_scene)
			return GAIA_ELOG_ERROR("Removing current level");
		auto prev = m_current_scene;
		m_current_scene = scn;
		m_current_scene->clear();
		m_current_scene->exit();
		delete m_current_scene;
		m_scenes.erase(lvl);
		m_current_scene = prev;
	}
	void Session::save_level(shared<Level> lvl)
	{
		if (m_current_level)
			m_scenes.erase(m_current_level);

		m_current_level = lvl;
		m_current_scene->save_level(lvl);
		m_scenes.emplace(m_current_level, m_current_scene);
	}

	shared<Camera> Session::get_active_camera()
	{
		if (m_editor)
			return m_current_scene->m_editor_camera;
		return m_current_scene->m_game_camera;
	}

	void Session::load()
	{
		// Check invalid next level
		if (!m_next_level)
			return GAIA_ELOG_WARN("Trying to load unexisting level");

		// If Current scene is not linked / Dummy
		if(!m_current_level && m_current_scene)
		{
			m_current_scene->exit();
			m_current_scene->clear();

			delete m_current_scene;
			m_current_scene = nullptr;
		}

		// Set new scene
		Scene * next = get_scene(m_next_level);

		// If not loaded, create it
		if (!next)
		{
			next = new Scene();
			m_current_scene = next;
			next->load_level(m_next_level);
			next->enter();
			m_scenes.emplace(m_next_level, next);
		}
		else
			m_current_scene = next;

		m_current_level = m_next_level;
		m_next_level = nullptr;
		m_state = e_State::update;
	}
	void Session::reload()
	{
		// Check invalid current level
		if (!m_current_level)
			return GAIA_ELOG_WARN("Trying to reload unexisting level");

		m_current_scene->clear();
		m_current_scene->exit();
		m_current_scene->load_level(m_current_level);
		m_current_scene->enter();
		m_state = e_State::update;
	}
	void Session::save()
	{
		// If Current scene is not linked / Dummy
		if (m_current_level)
		{
			auto s = get_scene(m_current_level);
			s->save_level(m_current_level);
		}
		else
		{
			Level::create("dummy");
			m_current_level = s_resources->get<Level>("dummy");
			m_scenes.emplace(m_current_level, m_current_scene);
			m_current_scene->save_level(m_current_level);
		}
	}
}
