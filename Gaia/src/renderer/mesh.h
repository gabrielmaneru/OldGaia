#pragma once

namespace Gaia {
	class VertexBuf
	{
	public:
		VertexBuf(u32 size);
		void create();
		void destroy();
		virtual void load();

		std::vector<u32> m_indices;
		std::vector<vec3> m_position;
		std::vector<vec3> m_normal;
		std::vector<vec2> m_uv_coord;
		std::vector<vec3> m_tangent;
		std::vector<vec3> m_bitangent;

	protected:
		virtual u32 get_vb_count()const{ return 6; }

		u32 m_size;
		std::vector<u32> m_vbo;
	};
	class AnimVertexBuf : public VertexBuf
	{
	public:
		AnimVertexBuf(u32 size);
		void load()override;
		std::vector<vec4> m_weights;
		std::vector<ivec4> m_boneid;

	protected:
		u32 get_vb_count()const override{ return 8; }
	};
	class Mesh {
	public:
		Mesh(u32 size);
		~Mesh();

		void load();
		void draw();

	private:
		VertexBuf m_vbo;
		u32 m_vao;
	};
}