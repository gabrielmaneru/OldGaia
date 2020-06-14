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

		void on_key_pressed(const KeyPressed_Event& event);

	private:

	};
}