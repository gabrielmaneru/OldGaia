#pragma once
#include <components/component.h>

namespace Gaia {
	class CameraController : public Component {
	public:
		void initialize()override;
		void enter()override;
		void update(float dt)override;
		void exit()override;

	private:

	};
}