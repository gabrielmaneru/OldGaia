#include "gaia_pch.h"
#include "window.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

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
		m_native = glfwCreateWindow((int)canvas.x, (int)canvas.y, title.c_str(), nullptr, nullptr);
		++s_window_count;

		// Create context
		glfwMakeContextCurrent(m_native);
		GAIA_EASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Glad failed to initialize");

		glfwSetWindowUserPointer(m_native, this);
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
		glfwSetKeyCallback(m_native, [](GLFWwindow*n, int key, int, int action, int)->void {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(n));
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressed_Event event;
					event.m_key = key;
					EventDispatcher::trigger_event(event);
					w->m_keyboard.insert(key);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleased_Event event;
					event.m_key = key;
					EventDispatcher::trigger_event(event);
					w->m_keyboard.erase(key);
					break;
				}
			}
		});
		// Set Char Key Callback
		glfwSetCharCallback(m_native, [](GLFWwindow*, u32 key)->void {
			KeyTyped_Event event;
			event.m_key = (int)key;
			EventDispatcher::trigger_event(event);
		});
		// Set Mouse Button Callback
		glfwSetMouseButtonCallback(m_native, [](GLFWwindow* n, int button, int action, int) {
			Window* w = static_cast<Window*>(glfwGetWindowUserPointer(n));
			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressed_Event event;
					event.m_button = button;
					EventDispatcher::trigger_event(event);
					w->m_mousebut.insert(button);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleased_Event event;
					event.m_button = button;
					EventDispatcher::trigger_event(event);
					w->m_mousebut.erase(button);
					break;
				}
			}
		});
		// Set Scroll Callback
		glfwSetScrollCallback(m_native, [](GLFWwindow* window, double xOff, double yOff) {
			MouseScrolled_Event event;
			event.m_xOff = (float)xOff;
			event.m_yOff = (float)yOff;
			EventDispatcher::trigger_event(event);
		});
		// Set Cursor Pos Callback
		glfwSetCursorPosCallback(m_native, [](GLFWwindow* window, double x, double y) {
			static bool first = true;
			static double prevx, prevy;
			if (first)
				prevx=x,prevy=y,
				first = false;

			MouseMoved_Event event;
			event.m_x = (float)x;
			event.m_y = (float)y;
			event.m_xOff = (float)(x - prevx);
			event.m_yOff = (float)(prevy - y);
			EventDispatcher::trigger_event(event);

			prevx = x, prevy = y;
		});

		// Create ImGui cursors
		m_cursors[ImGuiMouseCursor_Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_cursors[ImGuiMouseCursor_TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		m_cursors[ImGuiMouseCursor_ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_cursors[ImGuiMouseCursor_ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		m_cursors[ImGuiMouseCursor_ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		m_cursors[ImGuiMouseCursor_ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_cursors[ImGuiMouseCursor_ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_cursors[ImGuiMouseCursor_Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

		// Maximize Window
		glfwMaximizeWindow(m_native);
		{
			int width, height;
			glfwGetWindowSize(m_native, &width, &height);
			m_canvas = { (u32)width, (u32)height };
		}
	}
	Window::~Window() {
		glfwDestroyWindow(m_native);

		if (--s_window_count == 0)
			glfwTerminate();
	}
	void Window::update() {
		glfwSwapBuffers(m_native);
		glfwPollEvents();

		KeyDown_Event e1;
		for (auto k : m_keyboard)
		{
			e1.m_key = k;
			EventDispatcher::trigger_event(e1);
		}
		MouseDown_Event e2;
		for (auto k : m_mousebut)
		{
			e2.m_button = k;
			EventDispatcher::trigger_event(e2);
		}
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