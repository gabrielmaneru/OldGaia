#pragma once
#include "gaia_pch.h"
#include "window.h"
#include <events/event_handler.h>

namespace Gaia {
	class Engine : public EventListener{
	public:
		Engine();
		virtual ~Engine();
		virtual void run()final;

		void on_window_close(const WindowClose_Event & event);
		
	private:
		bool m_running;
		Window* m_window;
	};
}
