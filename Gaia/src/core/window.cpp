#include "gaia_pch.h"
#include "window.h"
#include<platform/GLFW_window.h>
namespace Gaia{
	Window* Window::create(const std::string & title, urect canvas)
	{
		// Assume Platform is windows
		return new GLFW_window{ title, canvas };
	}
}