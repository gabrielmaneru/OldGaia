#pragma once
#include <renderer/shader.h>
#include <renderer/framebuffer.h>
#include <renderer/renderable.h>

namespace Gaia {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render();
		void register_renderable(Renderable*);
		void unregister_renderable(Renderable*);

		void set_viewport(urect size);
		u32 get_final_texture_id(u32 id)const;
		
		urect m_viewport_size{1920, 1080};
		friend class Editor;
	private:
		std::set<Renderable*> m_renderables;
		Shader* m_shader_gbuffer;
		Shader* m_shader_debug;
		Framebuffer* m_gbuffer;
		Framebuffer* m_fb_final;
	};
}