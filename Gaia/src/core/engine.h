#pragma once
#include "gaia_pch.h"
#include <core/window.h>
#include <core/session.h>
#include <renderer/renderer.h>
#include <events/event_listener.h>

namespace Gaia {
	class Engine : public EventListener{
	public:
		Engine();
		void run();
		virtual ~Engine();

		void on_window_close(const WindowClose_Event & event);

	protected:
		Session* m_session;

	private:
		float m_timestep;
		float m_last_frametime{0.0f};
		bool m_running;
	};

	extern Engine* s_engine;
	extern Window* s_window;
	extern Renderer* s_renderer;
}
