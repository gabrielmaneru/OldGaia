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
			GAIA_EASSERT(glfwInit(), "GLFW failed to initialize");
			glfwSetErrorCallback([](int e, const char* desc)->void
			{
				GAIA_ELOG_ERROR("GLFW Error ({0}): {1}", e, desc);
			});
		}
		// Create window
		GAIA_ELOG_INFO("Creating window \"{0}\" (x:{1}, y:{2})", title, canvas.x, canvas.y);
		m_native = glfwCreateWindow((int)canvas.x, (int)canvas.y, title.c_str(), nullptr, nullptr);
		++s_window_count;
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

	void GLFW_window::setup()
	{
		// Create context
		m_context = Context::create_context(m_native);
		set_vsync(true);
		m_minimized = false;

		register_event(*this, &GLFW_window::on_window_resize);
		glfwSetWindowSizeCallback(m_native, [](GLFWwindow*, int w, int h)->void
		{
			WindowResize_Event event;
			event.m_canvas = { (u32)w,(u32)h };
			EventDispatcher::trigger_event(event);
		});
	}

	void GLFW_window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_native);
	}

	void GLFW_window::set_vsync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_vsync = enable;
	}

	void GLFW_window::on_window_resize(const WindowResize_Event & event)
	{
		m_minimized = event.m_canvas.x == 0 || event.m_canvas.y == 0;
	}
}
