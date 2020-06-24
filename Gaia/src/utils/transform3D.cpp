#include "gaia_pch.h"
#include "transform3D.h"

namespace Gaia {
	mat4 & Transform3D::get_matrix()
	{
		check_is(e_Mode::Matrix);
		return m_matrix;
	}
	vec3 & Transform3D::get_position()
	{
		check_is(e_Mode::Vector);
		return m_position;
	}
	quat & Transform3D::get_rotation()
	{
		check_is(e_Mode::Vector);
		return m_rotation;
	}
	vec3 & Transform3D::get_scale()
	{
		check_is(e_Mode::Vector);
		return m_scale;
	}
	const mat4 & Transform3D::get_matrix() const
	{
		check_is(e_Mode::Matrix);
		return m_matrix;
	}
	const vec3 & Transform3D::get_position() const
	{
		check_is(e_Mode::Vector);
		return m_position;
	}
	const quat & Transform3D::get_rotation() const
	{
		check_is(e_Mode::Vector);
		return m_rotation;
	}
	const vec3 & Transform3D::get_scale() const
	{
		check_is(e_Mode::Vector);
		return m_scale;
	}
	vec3 Transform3D::get_front()const
	{
		return rotate_unit_vec(vec3(0.f, 0.f, -1.f));
	}
	vec3 Transform3D::get_right()const
	{
		return rotate_unit_vec(vec3(1.f, 0.f, 0.f));
	}
	vec3 Transform3D::get_up()const
	{
		return rotate_unit_vec(vec3(0.f, 1.f, 0.f));
	}
	void Transform3D::check_is(e_Mode m) const
	{
		if (m_mode != m)
		{
			if (m_mode == e_Mode::Matrix)
				decompose();
			else
				compose();
		}
	}
	void Transform3D::compose()const
	{
		m_matrix = glm::scale(glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation), m_scale);
		m_mode  = e_Mode::Matrix;
	}

	void Transform3D::decompose()const
	{
		glm::decompose(m_matrix, m_scale, m_rotation, m_position, vec3{}, vec4{});

		
		m_mode = e_Mode::Vector;
	}
	vec3 Transform3D::rotate_unit_vec(const vec3 & v) const
	{
		if (m_mode == e_Mode::Matrix)
			return glm::normalize((vec3)(m_matrix*vec4(v, 0.f)));
		else
			return m_rotation * vec4(v, 0.f);
	}
}
