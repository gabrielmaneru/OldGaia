#include "sandbox_layer.h"

using namespace Gaia;

void SandboxLayer::begin()
{
	// Create Scene
	m_scene = new Scene("Sandbox");
	Engine::get()->set_active_scene(m_scene);

	// Add Cube Entity
	auto pE = m_scene->create_entity("Cube1");
	pE->add_component<MeshRenderable>();
}

void SandboxLayer::update()
{
}

void SandboxLayer::render_editor()
{
}

void SandboxLayer::end()
{
}
