#pragma once

namespace Gaia {
	struct VertexBuf
	{
	public:
		VertexBuf(u32 size);
		void create();
		void destroy();
		void load();

		std::vector<u32> m_indices;
		std::vector<vec3> m_position;
		std::vector<vec3> m_normal;
		std::vector<vec2> m_uv_coord;
		std::vector<vec3> m_tangent;
		std::vector<vec3> m_bitangent;
		std::vector<vec4> m_weights;
		std::vector<ivec4> m_boneid;

	private:
		u32 m_size;
		std::array<u32,8> m_vbo;
	};

	class Mesh {
	public:
		Mesh(u32 size);
		~Mesh();

		void load();
		void draw();

		friend class Model;

	private:
		VertexBuf m_vb;
		u32 m_vao;
	};
}