#pragma once
#include <events/event_handler.h>

struct GLFWwindow;
namespace Gaia {
	class Context;
}

namespace Gaia {
	struct WindowResize_Event : public iEvent{
		urect m_canvas;
	};
	struct WindowClose_Event : public iEvent {};


	class Window : public EventListener {
	public:
		Window(const std::string & title, urect canvas);
		~Window();

		void update();
		const std::string& get_title()const { return m_title; };
		urect get_canvas()const { return m_canvas; };
		void* get_native()const { return m_native; };
		bool get_minimized()const { return m_minimized; };
		bool get_vsync()const { return m_vsync; };
		void set_vsync(bool);

		void on_window_resize(const WindowResize_Event& event);

	private:
		std::string m_title;
		urect m_canvas;
		GLFWwindow* m_native;
		bool m_vsync;
		bool m_minimized;
		Unique<Context> m_context;
	};
}