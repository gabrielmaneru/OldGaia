#pragma once
#include <renderer/shader.h>
#include <renderer/framebuffer.h>

namespace Gaia {
	class Renderer {
	public:
		Renderer();
		void render();
		u32 get_final_texture_id()const;

	private:
		Shader* m_shader_debug;
		Framebuffer* m_fb;
	};
}