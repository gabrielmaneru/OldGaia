#include "gaia_pch.h"
#include "camera_controller.h"
#include <scene/entity.h>
#include <components/camera.h>

#include <GLFW/glfw3.h>
namespace Gaia {
	void CameraController::initialize()
	{
		check_dependency<Camera>();
		m_speed = 3.0f;
		m_angular_speed = 0.1f;
		m_yaw = 90.0f;
		m_pitch = 0.0f;
		recompute_rotation();
	}

	void CameraController::enter()
	{
		register_event(*this, &CameraController::on_key_down);
		register_event(*this, &CameraController::on_mousebut_down);
		register_event(*this, &CameraController::on_mouse_move);
	}

	void CameraController::update(float dt)
	{
		if (m_moving)
		{
			vec3 displ = m_owner->get_front() * m_keys[0]
				+ m_owner->get_right() * m_keys[1]
				+ m_owner->get_up() * m_keys[2];
			m_owner->get_position() += displ * m_speed * dt;

			m_yaw += m_mouse_off.x * m_angular_speed;
			m_pitch += m_mouse_off.y * m_angular_speed;
			m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
			recompute_rotation();
			m_moving = false;
		}

		m_keys = { 0,0,0 };
		m_mouse_off = { 0.0f };
	}

	void CameraController::exit()
	{
	}

	void CameraController::serialize(Json::Value & json) const
	{
		save(m_speed, json["Speed"]);
		save(m_angular_speed, json["AngularSpeed"]);
		save(m_yaw, json["Yaw"]);
		save(m_pitch, json["Pitch"]);
	}

	void CameraController::deserialize(const Json::Value & json)
	{
		load(m_speed, json["Speed"]);
		load(m_angular_speed, json["AngularSpeed"]);
		load(m_yaw, json["Yaw"]);
		load(m_pitch, json["Pitch"]);
	}

	void CameraController::on_key_down(const KeyDown_Event & event)
	{
		switch (event.m_key)
		{
		case GLFW_KEY_W:
			m_keys[0] = 1;
			break;
		case GLFW_KEY_S:
			m_keys[0] = -1;
			break;
		case GLFW_KEY_D:
			m_keys[1] = 1;
			break;
		case GLFW_KEY_A:
			m_keys[1] = -1;
			break;
		case GLFW_KEY_Q:
			m_keys[2] = 1;
			break;
		case GLFW_KEY_E:
			m_keys[2] = -1;
			break;
		default:
			break;
		}
	}
	void CameraController::on_mousebut_down(const MouseDown_Event & event)
	{
		switch (event.m_button)
		{
		case GLFW_MOUSE_BUTTON_RIGHT:
			m_moving = true;
			break;
		default:
			break;
		}
	}
	void CameraController::on_mouse_move(const MouseMoved_Event & event)
	{
		m_mouse_off = { event.m_xOff,event.m_yOff };
	}
	void CameraController::recompute_rotation()
	{
		vec3 front{
			cosf(glm::radians(m_yaw))* cosf(glm::radians(m_pitch)),
			sinf(glm::radians(m_pitch)),
			sinf(glm::radians(m_yaw))* cosf(glm::radians(m_pitch))
		};
		vec3 right = glm::normalize(glm::cross(front, vec3(0.f, 1.f, 0.f)));
		vec3 up = glm::normalize(glm::cross(right, front));
		m_owner->get_rotation() = glm::normalize(glm::quatLookAt(front, up));
	}
}
