#include "gaia_pch.h"
#include "component.h"

#include <components/camera.h>
#include <components/camera_controller.h>
#include <components/mesh_renderable.h>

namespace Gaia {
	const ComponentFactory & ComponentFactory::get()
	{
		static ComponentFactory m_factory{};
		return m_factory;
	}

	Component * ComponentFactory::create(const std::string& name) const
	{
		auto it = m_blueprints.find(name);
		if(it == m_blueprints.cend())
			return nullptr;
		return it->second->create();
	}

	ComponentFactory::ComponentFactory()
	{
		register_bp(new Camera());
		register_bp(new CameraController());
		register_bp(new MeshRenderable());
	}
	ComponentFactory::~ComponentFactory()
	{
		for (auto c : m_blueprints)
			delete c.second;
	}
	void ComponentFactory::register_bp(const Component * c)
	{
		m_blueprints[c->get_type_name()]=c;
	}
}
