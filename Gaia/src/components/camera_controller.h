#pragma once
#include <components/component.h>
#include <core/window.h>

namespace Gaia {

	class CameraController : public Component, public EventListener {
	public:
		void initialize()override;
		void enter()override;
		void update(float dt)override;
		void exit()override;

		void on_key_down(const KeyDown_Event& event);
		void on_mousebut_down(const MouseDown_Event& event);
		void on_mouse_move(const MouseMoved_Event& event);

	private:
		float m_yaw{ 90.f };
		float m_pitch{ 0.f };

		bool m_moving{false};
		vec3 m_keys{ 0 };
		float m_speed;
		float m_angular_speed;
		vec2 m_mouse_off{ 0.0f };
	};
}