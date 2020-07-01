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

		void set_viewport(urect size);
		u32 get_final_texture_id()const;
		
		urect m_viewport_size{1920, 1080};

	private:
		std::set<Renderable*> m_renderables;
		Shader* m_shader_debug;
		Framebuffer* m_fb;
	};
}