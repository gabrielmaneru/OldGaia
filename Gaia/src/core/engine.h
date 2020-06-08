#pragma once
#include "gaia_pch.h"
#include <core/window.h>
#include <core/layer.h>
#include <editor/editor.h>
#include <events/event_listener.h>

namespace Gaia {
	class Engine : public EventListener{
	public:
		Engine();
		virtual ~Engine();

		void run();
		template<typename L>
		void add_layer(L*p) {
			m_layers.emplace_back(std::unique_ptr<L>(p));
		}
		static Engine * get();
		Window * get_window() { return m_window; }
		LayerList& get_layers() { return m_layers; }

		void on_window_close(const WindowClose_Event & event);

		
	private:
		bool m_running;
		Window* m_window;
		Editor* m_editor;
		LayerList m_layers;
	};
}
