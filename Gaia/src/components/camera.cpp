#include "gaia_pch.h"
#include "camera.h"
#include <scene/scene.h>

namespace Gaia {
	void Camera::initialize()
	{
		m_projection = e_Projection::Perspective;
		m_fov_axis = e_FOV_Axis::Vertical;
		m_fov = 60.0f;
		m_clip_planes = { .3f, 1000.f };
		m_viewport = { 0.f, 0.f, 1.f, 1.f };
	}
	void Camera::enter()
	{
		Scene::s_active_scene->add_camera(m_owner->get_component<Camera>());
	}
	void Camera::exit()
	{
		Scene::s_active_scene->rem_camera(m_owner->get_component<Camera>());
	}
	mat4 Camera::get_projection(vec2 view_size) const
	{
		return glm::perspectiveFov(glm::radians(m_fov), view_size.x, view_size.y, m_clip_planes.x, m_clip_planes.y);
	}
}
