#include "sandbox_layer.h"

using namespace Gaia;

void SandboxLayer::begin()
{
	// Create Scene
	m_scene = new Scene("Sandbox");

	// Add Camera
	auto pE = m_scene->create_entity("Camera");
	pE->add_component<CameraController>();
	pE->enter();
	pE->get_position() = vec3(-2.0f, 2.0f, -10.0f);

	// Add Cube Entity
	pE = m_scene->create_entity("Cube1");
	pE->add_component<MeshRenderable>();
	pE->enter();
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
