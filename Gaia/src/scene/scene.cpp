#include "gaia_pch.h"
#include "scene.h"

namespace Gaia {
	Scene* Scene::s_active_scene = nullptr;

	Scene::Scene(const std::string & name)
		: m_name(name) {

		if (!s_active_scene)
			s_active_scene = this;
	}
	Scene::~Scene()	{
		for (auto pE : m_entities)
			delete pE;
		if (s_active_scene == this)
			s_active_scene = nullptr;
	}
	void Scene::update(float dt)
	{
		for (auto pE : m_entities)
			pE->update(dt);
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
}
