#include <gaia.h>
#include <core/entry_point.h>

class Sandbox : public Gaia::Engine {
public:
	Sandbox::Sandbox(){
		// Create Scene
		auto lvl = Gaia::s_resources->get<Gaia::Level>("dummy");
		if (lvl)
		{
			m_session->load_level(lvl);
		}
		else
		{
			auto scn = m_session->get_current_scene();
			// Add Camera
			auto pE = scn->create_entity("Camera");
			pE->add_component<Gaia::CameraController>();
			pE->get_position() = vec3(-2.0f, 2.0f, -10.0f);

			// Add Cube Entity
			pE = scn->create_entity("Cube1");
			pE->add_component<Gaia::MeshRenderable>();
		}
	}
	Sandbox::~Sandbox() {

		// Save the Level
		//Json::Value m_data{};
		//save(*m_scene, m_data);
		//
		//// Update the level file
		//std::ofstream file("scene.json");
		//file << m_data;
	}
};

Gaia::Engine* Gaia::create_program() {
	static Sandbox* instance = new Sandbox();
	return instance;
}
