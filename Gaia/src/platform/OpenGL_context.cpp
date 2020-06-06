#include "gaia_pch.h"
#include "OpenGL_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Gaia {
	OpenGL_context::OpenGL_context(GLFWwindow * native)
		: m_native{native}
	{
		glfwMakeContextCurrent(native);
		GAIA_EASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Glad failed to initialize");

		// Output device properties
		GAIA_ELOG_INFO("OpenGL Info:");
		GAIA_ELOG_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		GAIA_ELOG_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		GAIA_ELOG_INFO("Version: {0}", glGetString(GL_VERSION));
		GAIA_ELOG_INFO("GLSL: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));

		int vMaj, vMin;
		glGetIntegerv(GL_MAJOR_VERSION, &vMaj);
		glGetIntegerv(GL_MINOR_VERSION, &vMin);
		GAIA_EASSERT(vMaj > 4 || (vMaj == 4 && vMin >= 5), "OpenGL v4.5 required (current is {0}.{1})", vMaj, vMin);
	}
	void OpenGL_context::swap_buffers()
	{
		glfwSwapBuffers(m_native);
	}
}
