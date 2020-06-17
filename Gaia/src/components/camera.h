#pragma once
#include <components/component.h>

namespace Gaia {
	class Camera : public Component {
	public:
		void initialize()override;
		void enter()override;
		void exit()override;

		mat4 get_projection(urect view_size)const;

	private:
		enum class e_Projection {
			Perspective, Orthographic
		} m_projection;
		enum class e_FOV_Axis {
			Vertical, Horizontal
		} m_fov_axis;
		float m_fov;
		vec2 m_clip_planes;
		vec4 m_viewport;
	};
}