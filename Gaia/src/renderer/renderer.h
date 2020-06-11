#pragma once
#include <renderer/shader.h>
#include <renderer/framebuffer.h>
#include <renderer/renderable.h>

namespace Gaia {
	class Renderer {
	public:
		Renderer();

		void render();
		void register_renderable(Renderable*);
		void unregister_renderable(Renderable*);

		u32 get_final_texture_id()const;


	private:
		std::set<Renderable*> m_renderables;
		Shader* m_shader_debug;
		Framebuffer* m_fb;
	};
}