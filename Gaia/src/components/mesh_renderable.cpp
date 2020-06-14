#include "gaia_pch.h"
#include "mesh_renderable.h"
namespace Gaia {
	void MeshRenderable::initialize()
	{
		m_visible = true;
	}
	void MeshRenderable::enter()
	{
		m_model = new Model("assets/meshes/cube.obj", e_Extension::obj);
		m_model->load_internal();
	}
	void MeshRenderable::update(float dt)
	{
	}
	void MeshRenderable::draw() const
	{
		m_model->draw();
	}
	void MeshRenderable::exit()
	{
		delete m_model;
	}
}