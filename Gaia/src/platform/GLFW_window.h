#pragma once
#include "gaia_pch.h"
#include <core/window.h>
#include <events/event_handler.h>
#include <renderer/context.h>

#include <GLFW/glfw3.h>

namespace Gaia {
	class WindowResize_Event : public iEvent
	{
	public:
		urect m_canvas;
	};

	class GLFW_window : public Window, public EventHandler
	{
	public:
		GLFW_window(const std::string & title, urect canvas);
		virtual ~GLFW_window();

		void setup() override;
		void update() override;
		const std::string& get_title() const override { return m_title; }
		urect get_canvas()const override { return m_canvas; }
		void* get_native()const override { return m_native; }
		bool get_minimized()const override { return m_minimized; }
		bool get_vsync()const override { return m_vsync; }
		void set_vsync(bool);

		void on_window_resize(const WindowResize_Event& event);

	private:
		std::string m_title;
		urect m_canvas;
		GLFWwindow* m_native;
		bool m_vsync;
		bool m_minimized;
		Context* m_context;
	};
}