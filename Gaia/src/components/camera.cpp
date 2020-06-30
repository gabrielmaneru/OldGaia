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

		auto scn = s_session->get_current_scene();
		auto cam = m_owner->get_component<Camera>();
		if (!scn->m_editor_camera)
			scn->m_editor_camera = cam, m_is_editor_cam = true;
		else if (!scn->m_game_camera)
			scn->m_game_camera = cam, m_is_game_cam = true;
	}
	void Camera::enter()
	{
		initialize();
		auto scn = s_session->get_current_scene();
		auto cam = m_owner->get_component<Camera>();
		if (m_is_editor_cam)
			scn->m_editor_camera = cam;
		if (m_is_game_cam)
			scn->m_game_camera = cam;
	}
	void Camera::exit()
	{
		auto scn = s_session->get_current_scene();
		auto cam = m_owner->get_component<Camera>();

		if (scn->m_editor_camera == cam)
			scn->m_editor_camera = nullptr;
		if (scn->m_game_camera == cam)
			scn->m_game_camera = nullptr;
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
		save(m_is_editor_cam, json["IsEditorCam"]);
		save(m_is_game_cam, json["IsGameCam"]);
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
		load(m_is_editor_cam, json["IsEditorCam"]);
		load(m_is_game_cam, json["IsGameCam"]);
	}
	mat4 Camera::get_projection(urect view_size) const
	{
		return glm::perspectiveFov(glm::radians(m_fov_angle), (float)view_size.x, (float)view_size.y, m_clip_planes.x, m_clip_planes.y);
	}
}
