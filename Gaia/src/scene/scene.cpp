#include "gaia_pch.h"
#include "scene.h"

namespace Gaia {
	Scene::~Scene()	{
		clear();
	}
	void Scene::load_level(shared<Level> lvl)
	{
		if (!lvl)
			GAIA_ELOG_ERROR("Loading null level");
		m_level = lvl;
		lvl->load_level(this);
	}
	void Scene::save_level(shared<Level> lvl)
	{
		if (!lvl)
			GAIA_ELOG_ERROR("Saving null level");
		m_level = lvl;
		lvl->save_level(this);
	}
	void Scene::enter()
	{
		for (auto pE : m_entities)
			pE->enter();
	}
	void Scene::update(float dt)
	{
		for (auto pE : m_entities)
			pE->update(dt);
	}
	void Scene::exit()
	{
		for (auto pE : m_entities)
			pE->exit();
	}
	void Scene::clear()
	{
		for (auto pE : m_entities)
			delete pE;
		m_entities.clear();
		m_cameras.clear();
	}
	Entity * Scene::create_entity(const std::string & name)	{
		m_entities.push_back(new Entity(name));
		return m_entities.back();
	}
	void Scene::add_camera(const shared<Camera>& cam)
	{
		m_cameras.push_back(cam);
	}
	void Scene::rem_camera(const shared<Camera>& cam)
	{
		auto it = std::find(m_cameras.begin(), m_cameras.end(), cam);
		if (it != m_cameras.end())
			m_cameras.erase(it);
	}
	void Scene::serialize(Json::Value & json) const
	{
		save(m_entities, json);
	}
	void Scene::deserialize(const Json::Value & json)
	{
		load(m_entities, json);
	}
}
