#include "gaia_pch.h"
#include "context.h"
#include <platform/OpenGL_context.h>

#include <GLFW/glfw3.h>

namespace Gaia {
	Context* Context::create_context(void * native)
	{
		// Assume Renderer is OpenGL
		return new OpenGL_context{ static_cast<GLFWwindow*>(native) };
	}
}
