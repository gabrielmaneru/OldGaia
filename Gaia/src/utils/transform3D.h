#pragma once

namespace Gaia {
	class Transform3D
	{
	public:
		mat4& get_matrix();
		vec3& get_position();
		quat& get_rotation();
		vec3& get_scale();
		const mat4& get_matrix()const;
		const vec3& get_position()const;
		const quat& get_rotation()const;
		const vec3& get_scale()const;

		vec3 get_front()const;
		vec3 get_right()const;
		vec3 get_up()const;

	private:
		enum class e_Mode { Vector, Matrix };
		void check_is(e_Mode m)const;
		void compose()const;
		void decompose()const;
		vec3 rotate_unit_vec(const vec3& v)const;

		mutable e_Mode m_mode{e_Mode::Matrix};
		mutable mat4 m_matrix{ 1.0f };
		mutable vec3 m_position;
		mutable quat m_rotation;
		mutable vec3 m_scale;
	};
}