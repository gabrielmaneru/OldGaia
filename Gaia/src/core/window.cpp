#include "gaia_pch.h"
#include "window.h"
#include<platform/GLFW_window.h>
namespace Gaia{
	Unique<Window> Window::create(const std::string & title, urect canvas)
	{
		return create_unique<GLFW_window>(title, canvas);
	}
}