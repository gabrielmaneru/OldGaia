#pragma once
#include <components/component.h>

namespace Gaia {
	class Camera : public Component {
		DECL_COMP(Camera)
	public:
		void initialize()override;
		void enter()override;
		void exit()override;
		void serialize(Json::Value& json)const override;
		void deserialize(const Json::Value& json)override;
		std::string get_type_name()const override { return "Camera"; }

		mat4 get_projection(urect view_size)const;

	private:
		enum class e_Projection {
			Perspective, Orthographic
		} m_projection;
		enum class e_FOV_Axis {
			Vertical, Horizontal
		} m_fov_axis;
		float m_fov_angle;
		vec2 m_clip_planes;
		vec4 m_viewport;
		bool m_is_editor_cam{ false };
		bool m_is_game_cam{ false };
	};
}