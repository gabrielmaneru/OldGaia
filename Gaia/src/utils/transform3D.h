#pragma once

namespace Gaia {
	class Transform3D
	{
	public:
		mat4& get_matrix();
		vec3& get_position();
		quat& get_rotation();
		vec3& get_scale();
		vec3 get_front();
		vec3 get_right();
		vec3 get_up();

	private:
		void compose();
		void decompose();
		vec3 rotate_unit_vec(const vec3& v)const;

		bool m_is_composed{true};
		mat4 m_matrix{ 1.0f };
		vec3 m_position;
		quat m_rotation;
		vec3 m_scale;
	};
}