#include "gaia_pch.h"
#include "renderer.h"
#include <core/engine.h>
#include <renderer/texture2D.h>

#include <Glad/glad.h>

namespace Gaia {
	static u32 vao =0;
	Renderer::Renderer()
	{
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)->void
		{

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				GAIA_ELOG_CRITICAL("[OpenGL Debug HIGH] {0}", message);
				GAIA_EASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				GAIA_ELOG_WARN("[OpenGL Debug MEDIUM] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_LOW:
				GAIA_ELOG_INFO("[OpenGL Debug LOW] {0}", message);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				//GAIA_ELOG_TRACE("[OpenGL Debug NOTIFICATION] {0}", message);
				break;
			}
		}, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		GAIA_ELOG_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GAIA_ELOG_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GAIA_ELOG_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &TextureProps::max_anisotropy);

		m_shader_debug = new Shader("Debug",
			std::vector<std::string>{
				"assets/shaders/debug.vert",
				"assets/shaders/debug.frag"
		});
		m_fb = new Framebuffer(s_window->get_canvas(),
			FramebufferProperties{
				Texture::default_color_rgba,
				Texture::default_depth
			});

		float vertices[] = {
						-1.f, -1.f,
						 3.f, -1.f,
						-1.f,  3.f,
		};
		unsigned int VBO;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

	}


	void Renderer::render()
	{
		// Clear Full Window
		//urect canvas = Engine::get_window()->get_canvas();
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glViewport(0, 0, canvas.x, canvas.y);
		//glClearColor(1.f, 0.f, 0.f, 0.f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render To FB
		m_fb->bind();
		glClearColor(1.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (s_session->get_current_scene())
		{
			m_shader_debug->bind();
			auto cam = s_session->get_active_camera();
			mat4 p = cam->get_projection(m_viewport_size);
			m_shader_debug->set_uniform("P", p);
			mat4 v = cam->get_view();
			m_shader_debug->set_uniform("V", v);
			m_shader_debug->set_uniform("M", mat4(1.0f));
			for (auto r : m_renderables)
				r->draw();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::register_renderable(Renderable * p)
	{
		auto res = m_renderables.find(p);
		if (res != m_renderables.end())
			GAIA_ELOG_WARN("Renderable already registered");
		else
			m_renderables.emplace(p);
	}

	void Renderer::unregister_renderable(Renderable * p)
	{
		auto res = m_renderables.find(p);
		if (res != m_renderables.end())
			m_renderables.erase(res);
		else
			GAIA_ELOG_WARN("Invalid Renderable Unregister");
	}

	void Renderer::set_viewport(urect size)
	{
		m_viewport_size = size;
		m_fb->resize(size);
	}

	u32 Renderer::get_final_texture_id() const
	{
		return m_fb->get_txt_id(0);
	}
}
