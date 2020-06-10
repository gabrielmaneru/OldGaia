#include "gaia_pch.h"
#include "scene.h"

namespace Gaia {
	Scene::Scene(const std::string & name)
		: m_name(name) {}
	Scene::~Scene()
	{
		for (auto pE : m_entities)
			delete pE;
	}
	Entity * Scene::create_entity(const std::string & name)
	{
		m_entities.push_back(new Entity(name));
		return m_entities.back();
	}
}
