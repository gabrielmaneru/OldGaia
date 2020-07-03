#include "gaia_pch.h"
#include "mesh_renderable.h"
#include <scene/entity.h>
#include <core/session.h>

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

		m_material = s_resources->get<Material>("grass");
		if (!m_material)
		{
			Material::create("grass");
			m_material = s_resources->get<Material>("grass");
			m_material->save_material();
		}
	}
	void MeshRenderable::update(float dt)
	{
	}
	void MeshRenderable::draw(Shader * shader) const
	{
		if (!m_visible)
			return;

		shader->set_uniform("M", m_owner->get_matrix());
		m_model->draw();
	}
	void MeshRenderable::render_editor()
	{
		ImGui::Text("Model"); ImGui::SameLine();
		ImGui::Selectable(m_model->get_name().c_str());

		ImGui::Text("Material"); ImGui::SameLine();
		std::string name;
		if (m_material)
			name = m_material->get_name();
		else
			name = "...";
		if (ImGui::Button(name.c_str()))
			ImGui::OpenPopup("select_material");
		ImGui::SameLine();
		if (m_material && ImGui::Button("Edit"))
			ImGui::OpenPopup("edit_material");
		select_material(m_material);
		edit_material(m_material);
		
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