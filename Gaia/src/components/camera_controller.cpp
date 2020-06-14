#include "gaia_pch.h"
#include "camera_controller.h"
#include <scene/entity.h>
#include <components/camera.h>

#include <GLFW/glfw3.h>
namespace Gaia {
	void CameraController::initialize()
	{
		check_dependency<Camera>();
		register_event(*this, &CameraController::on_key_pressed);
	}

	void CameraController::enter()
	{
	}

	void CameraController::update(float dt)
	{
		
	}

	void CameraController::exit()
	{
	}
	void CameraController::on_key_pressed(const KeyPressed_Event & event)
	{
		switch (event.m_key)
		{
		case GLFW_KEY_W:
			m_owner->get_position() += m_owner->get_front();
			break;
		case GLFW_KEY_S:
			m_owner->get_position() -= m_owner->get_front();
			break;
		case GLFW_KEY_D:
			m_owner->get_position() += m_owner->get_right();
			break;
		case GLFW_KEY_A:
			m_owner->get_position() -= m_owner->get_right();
			break;
		case GLFW_KEY_Q:
			m_owner->get_position() += m_owner->get_up();
			break;
		case GLFW_KEY_E:
			m_owner->get_position() -= m_owner->get_up();
			break;
		default:
			break;
		}
	}
}
