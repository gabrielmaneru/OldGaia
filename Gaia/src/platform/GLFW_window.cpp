#include "gaia_pch.h"
#include "GLFW_window.h"
namespace Gaia {
	static u8 s_window_count{ 0 };

	GLFW_window::GLFW_window(const std::string & title, urect canvas)
		: m_title{ title }, m_canvas{ canvas }, m_native{ nullptr }
	{
		// Create window with specific data
		// Initialize GLFW once
		if (s_window_count == 0)
		{
			GAIA_ELOG_TRACE("Initializing GLFW");
			assert(glfwInit());
		}
		// Create window
		GAIA_ELOG_TRACE("Creating window {0} ({1}, {2})", title, canvas.x, canvas.y);
		m_native = glfwCreateWindow((int)canvas.x, (int)canvas.y, title.c_str(), nullptr, nullptr);
		++s_window_count;
		// Create context
		GAIA_ELOG_TRACE("Creating context");
		glfwMakeContextCurrent(m_native);
	}


	GLFW_window::~GLFW_window()
	{
		GAIA_ELOG_TRACE("Destoying window");
		glfwDestroyWindow(m_native);

		if (--s_window_count == 0)
		{
			GAIA_ELOG_TRACE("Terminating GLFW");
			glfwTerminate();
		}
	}

	void GLFW_window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_native);
	}
}
