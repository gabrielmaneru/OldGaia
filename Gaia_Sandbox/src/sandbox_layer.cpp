#include "sandbox_layer.h"

using namespace Gaia;

void SandboxLayer::begin()
{
	// Create Scene
	m_scene = new Scene("Sandbox");

	if (1)
	{
		std::ifstream file;
		file.open("scene.json");
	
		// Read the data
		Json::Value m_data{};
		file >> m_data;
	
		load(*m_scene, m_data);
	}
	else
	{
		// Add Camera
		auto pE = m_scene->create_entity("Camera");
		pE->add_component<CameraController>();
		pE->get_position() = vec3(-2.0f, 2.0f, -10.0f);
		
		// Add Cube Entity
		pE = m_scene->create_entity("Cube1");
		pE->add_component<MeshRenderable>();
	}
	m_scene->enter();
}

void SandboxLayer::update()
{
	m_scene->update(1.0f/60.0f);
}

void SandboxLayer::render_editor()
{
}

void SandboxLayer::end()
{
	m_scene->exit();
	//// Save the Level
	Json::Value m_data{};
	save(*m_scene, m_data);
	
	// Update the level file
	std::ofstream file("scene.json");
	file << m_data;
}
