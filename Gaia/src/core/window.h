#pragma once
#include <events/event_listener.h>

struct GLFWwindow;
struct GLFWcursor;

namespace Gaia {
	struct WindowResize_Event : public iEvent { urect m_canvas; };
	struct WindowClose_Event : public iEvent {};
	struct KeyPressed_Event     : public iEvent { int m_key, m_repeat; };
	struct KeyReleased_Event    : public iEvent { int m_key; };
	struct KeyTyped_Event       : public iEvent { int m_key; };
	struct MousePressed_Event   : public iEvent { int m_button; };
	struct MouseReleased_Event : public iEvent { int m_button; };
	struct MouseScrolled_Event : public iEvent { double m_xOff, m_yOff; };
	struct MouseMoved_Event  : public iEvent { double m_x, m_y; };

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
		GLFWcursor* m_cursors[8];
		bool m_vsync;
		bool m_minimized;
	};
}