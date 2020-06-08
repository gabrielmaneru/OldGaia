#pragma once
#include "gaia_pch.h"
#include <core/window.h>
#include <core/layer.h>
#include <renderer/renderer.h>
#include <editor/editor.h>
#include <events/event_listener.h>

namespace Gaia {
	class Engine : public EventListener{
	public:
		Engine();
		virtual ~Engine();

		void run();
		template<typename L>
		void add_layer(std::shared_ptr<L>&& p) {
			m_layers.emplace_back(p);
		}
		void run_layers(std::function<void(std::shared_ptr<Layer>)> func);

		void on_window_close(const WindowClose_Event & event);

		
	private:
		bool m_running;
		Window* m_window;
		Renderer* m_renderer;
		Editor* m_editor;
		LayerList m_layers;

	public:
		static Engine* get();
		static Window* get_window();
		static Renderer* get_renderer();
	};
}
