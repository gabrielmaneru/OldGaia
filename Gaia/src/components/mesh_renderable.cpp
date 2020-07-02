#include "gaia_pch.h"
#include "mesh_renderable.h"
#include <scene/entity.h>

#include <imgui/imgui.h>

namespace Gaia {
	void MeshRenderable::initialize()
	{
		m_visible = true;
	}
	void MeshRenderable::enter()
	{
		register_renderable();
		m_model = new Model("assets/meshes/cube.obj", e_Extension::obj);
		m_model->load_internal();
	}
	void MeshRenderable::update(float dt)
	{
	}
	void MeshRenderable::draw(Shader * shader) const
	{
		shader->set_uniform("M", m_owner->get_matrix());
		m_model->draw();
	}
	void MeshRenderable::render_editor()
	{
		ImGui::Text(m_model->get_name().c_str());
	}
	void MeshRenderable::exit()
	{
		delete m_model;
		unregister_renderable();
	}
	void MeshRenderable::serialize(Json::Value & json) const
	{
		save(m_visible, json["Visible"]);
	}
	void MeshRenderable::deserialize(const Json::Value & json)
	{
		load(m_visible, json["Visible"]);
	}
}