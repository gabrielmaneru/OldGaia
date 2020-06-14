#include "gaia_pch.h"
#include "transform3D.h"

namespace Gaia {
	mat4 & Transform3D::get_matrix()
	{
		if (!m_is_composed)
			compose();
		return m_matrix;
	}
	vec3 & Transform3D::get_position()
	{
		if (m_is_composed)
			decompose();
		return m_position;
	}
	quat & Transform3D::get_rotation()
	{
		if (m_is_composed)
			decompose();
		return m_rotation;
	}
	vec3 & Transform3D::get_scale()
	{
		if (m_is_composed)
			decompose();
		return m_scale;
	}
	vec3 Transform3D::get_front()
	{
		return rotate_unit_vec(vec3(0.f, 0.f, -1.f));
	}
	vec3 Transform3D::get_right()
	{
		return rotate_unit_vec(vec3(1.f, 0.f, 0.f));
	}
	vec3 Transform3D::get_up()
	{
		return rotate_unit_vec(vec3(0.f, 1.f, 0.f));
	}
	void Transform3D::compose()
	{
		m_matrix = glm::scale(glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation), m_scale);
		m_is_composed = false;
	}

	void Transform3D::decompose()
	{
		m_position = vec3(m_matrix[3]);

		m_rotation = glm::quatLookAt(vec3(m_matrix[2]), vec3(m_matrix[1]));

		m_scale = vec3(
			glm::length(m_matrix[0]),
			glm::length(m_matrix[1]),
			glm::length(m_matrix[2])
		);
		m_is_composed = false;
	}
	vec3 Transform3D::rotate_unit_vec(const vec3 & v) const
	{
		if (m_is_composed)
			return glm::normalize((vec3)(m_matrix*vec4(v, 0.f)));
		else
			return m_rotation * vec4(v, 0.f);
	}
}
