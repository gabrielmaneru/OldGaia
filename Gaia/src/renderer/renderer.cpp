#include "gaia_pch.h"
#include "renderer.h"
#include <core/engine.h>

#include <Glad/glad.h>

Gaia::Renderer::Renderer()
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

}


void Gaia::Renderer::render()
{
	urect canvas = Engine::get_window()->get_canvas();
	glViewport(0, 0, canvas.x, canvas.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.3f, 0.f, .3f, 1.f);
}
