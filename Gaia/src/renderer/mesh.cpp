#include "gaia_pch.h"
#include "mesh.h"

#include <Glad/glad.h>

namespace Gaia {
	VertexBuf::VertexBuf(u32 size)
		: m_size(size)
	{
		m_position.resize(size, vec3{ 0.0f });
		m_normal.resize(size, vec3{ 0.0f });
		m_uv_coord.resize(size, vec2{ 0.0f });
		m_tangent.resize(size, vec3{ 0.0f });
		m_bitangent.resize(size, vec3{ 0.0f });
		m_weights.resize(size, vec4{ 0.0f });
		m_boneid.resize(size, ivec4{ 0 });
	}
	void VertexBuf::create()
	{
		glGenBuffers(m_vbo.size(), m_vbo.data());
	}
	void VertexBuf::destroy()
	{
		glDeleteBuffers(m_vbo.size(), m_vbo.data());
	}
	void VertexBuf::load()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(u32), m_indices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec3), m_position.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec3), m_normal.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec2), m_uv_coord.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec3), m_tangent.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec3), m_bitangent.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(vec4), m_weights.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(ivec4), m_boneid.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(6);
		glVertexAttribIPointer(6, 4, GL_INT, 0, nullptr);
	}

	Mesh::Mesh(u32 size)
		: m_vb(size)
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		m_vb.create();
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glBindVertexArray(m_vao);
		m_vb.destroy();
		glDeleteVertexArrays(1, &m_vao);
		glBindVertexArray(0);
	}
	void Mesh::load()
	{
		glBindVertexArray(m_vao);
		m_vb.load();
		glBindVertexArray(0);
	}
	void Mesh::draw()
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, (int)m_vb.m_indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}
