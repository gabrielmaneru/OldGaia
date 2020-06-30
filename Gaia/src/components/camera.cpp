#include "gaia_pch.h"
#include "camera.h"
#include <scene/scene.h>
#include <core/session.h>

namespace Gaia {
	void Camera::initialize()
	{
		m_projection = e_Projection::Perspective;
		m_fov_axis = e_FOV_Axis::Vertical;
		m_fov_angle = 60.0f;
		m_clip_planes = { .3f, 1000.f };
		m_viewport = { 0.f, 0.f, 1.f, 1.f };
	}
	void Camera::enter()
	{
		s_session->get_current_scene()->add_camera(m_owner->get_component<Camera>());
	}
	void Camera::exit()
	{
		s_session->get_current_scene()->rem_camera(m_owner->get_component<Camera>());
	}
	void Camera::serialize(Json::Value & json) const
	{
		u32 proj = (u32)m_projection;
		save(proj, json["Projection"]);
		u32 fov_axis = (u32)m_fov_axis;
		save(fov_axis, json["FovAxis"]);
		save(m_fov_angle, json["FovAngle"]);
		save(m_clip_planes, json["ClipPlanes"]);
		save(m_viewport, json["Viewport"]);
	}
	void Camera::deserialize(const Json::Value & json)
	{
		u32 proj;
		load(proj, json["Projection"]);
		m_projection = (e_Projection)proj;
		u32 fov_axis;
		load(fov_axis, json["FovAxis"]);
		m_fov_axis = (e_FOV_Axis)fov_axis;
		load(m_fov_angle, json["FovAngle"]);
		load(m_clip_planes, json["ClipPlanes"]);
		load(m_viewport, json["Viewport"]);
	}
	mat4 Camera::get_projection(urect view_size) const
	{
		return glm::perspectiveFov(glm::radians(m_fov_angle), (float)view_size.x, (float)view_size.y, m_clip_planes.x, m_clip_planes.y);
	}
}
