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

		GAIA_ELOG_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GAIA_ELOG_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GAIA_ELOG_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &TextureProperties::max_anisotropy);

		m_shader_debug = new Shader("Debug",
			std::vector<std::string>{
				"assets/shaders/debug.vert",
				"assets/shaders/debug.frag"
		});
		m_fb = new Framebuffer(Engine::get_window()->get_canvas(),
			FramebufferProperties{
				TextureProperties::default_color,
				TextureProperties::default_depth
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
		urect canvas = Engine::get_window()->get_canvas();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, canvas.x, canvas.y);
		glClearColor(1.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render To FB
		m_fb->bind();
		glClearColor(1.f, 0.f, 0.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader_debug->bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	u32 Renderer::get_final_texture_id() const
	{
		return m_fb->get_txt_id(0);
	}
}
