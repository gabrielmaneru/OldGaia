#include "gaia_pch.h"
#include "window.h"
#include <renderer/context.h>

#include <GLFW/glfw3.h>

namespace Gaia{
	static u8 s_window_count{ 0 };

	Window::Window(const std::string & title, urect canvas)
		:m_minimized(false) {
		// Create window with specific data
		// Initialize GLFW once
		if (s_window_count == 0) {
			GAIA_EASSERT(glfwInit(), "GLFW failed to initialize");
			glfwSetErrorCallback([](int e, const char* desc)->void {
				GAIA_ELOG_ERROR("GLFW Error ({0}): {1}", e, desc);
			});
		}
		// Create window
		GAIA_ELOG_INFO("Creating window \"{0}\" (x:{1}, y:{2})", title, canvas.x, canvas.y);
		m_native = glfwCreateWindow((int)canvas.x, (int)canvas.y, title.c_str(), nullptr, nullptr);
		++s_window_count;

		// Create context
		m_context = create_unique<Context>(m_native);

		// Activate V-Sync
		set_vsync(true);

		// Register Window Resize Event
		register_event(*this, &Window::on_window_resize);
		// Set Window Resize Callback
		glfwSetWindowSizeCallback(m_native, [](GLFWwindow*, int w, int h)->void {
			WindowResize_Event event;
			event.m_canvas = { (u32)w,(u32)h };
			EventDispatcher::trigger_event(event);
		});

		// Set Window Close Callback
		glfwSetWindowCloseCallback(m_native, [](GLFWwindow*)->void {
			EventDispatcher::trigger_event(WindowClose_Event{});
		});

		// Set Key Callback
		glfwSetKeyCallback(m_native, [](GLFWwindow*, int key, int, int action, int)->void {
			//TODO
		});
		// Set Char Key Callback
		glfwSetCharCallback(m_native, [](GLFWwindow*, u32 key)->void {
			//TODO
		});
		// Set Mouse Button Callback
		glfwSetMouseButtonCallback(m_native, [](GLFWwindow* window, int button, int action, int) {
			//TODO
		});
		// Set Scroll Callback
		glfwSetScrollCallback(m_native, [](GLFWwindow* window, double xOff, double yOff) {
			//TODO
		});
		// Set Cursor Pos Callback
		glfwSetCursorPosCallback(m_native, [](GLFWwindow* window, double x, double y) {
			//TODO
		});

	}
	Window::~Window() {
		GAIA_ELOG_TRACE("Destoying window");
		glfwDestroyWindow(m_native);

		if (--s_window_count == 0) {
			GAIA_ELOG_TRACE("Terminating GLFW");
			glfwTerminate();
		}
	}
	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(m_native);
	}
	void Window::set_vsync(bool enable) {
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_vsync = enable;
	}
	void Window::on_window_resize(const WindowResize_Event & event)	{
		m_minimized = event.m_canvas.x == 0 || event.m_canvas.y == 0;
	}
}