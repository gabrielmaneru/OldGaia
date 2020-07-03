#pragma once
#include <renderer/shader.h>
#include <renderer/framebuffer.h>
#include <renderer/renderable.h>

namespace Gaia {
	enum class e_BufferID;
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void render();
		void register_renderable(Renderable*);
		void unregister_renderable(Renderable*);

		void set_viewport(urect size);
		u32 get_render_buffer_txt_id(e_BufferID buf_id);
		
		urect m_viewport_size{1920, 1080};
		friend class Editor;
	private:
		std::set<Renderable*> m_renderables;
		Shader* m_shader_gbuffer;
		Shader* m_shader_debug;
		Framebuffer* m_fb_gbuffer;
		Framebuffer* m_fb_final;
	};

	enum class e_BufferID{
		Position, Albedo,MetalRough,
		Normal, Final
	};
}