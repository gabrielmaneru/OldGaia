#pragma once
#include "gaia_pch.h"
#include <core/layer.h>
#include <core/window.h>
#include <renderer/renderer.h>
#include <resources/resource_manager.h>
#include <editor/editor.h>
#include <scene/scene.h>
#include <events/event_listener.h>

namespace Gaia {
	class Engine : public EventListener{
	public:
		Engine();
		virtual ~Engine();

		void run();
		void run_command(LayerCommand cmd);
		template<typename L>
		void add_layer(std::shared_ptr<L>&& p) { m_layers.emplace_back(p); }
		
		void on_window_close(const WindowClose_Event & event);

		float m_timestep;
		float m_last_frametime{0.0f};

	private:
		bool m_running;
		Window* m_window;
		Renderer* m_renderer;
		ResourceManager* m_resources;

		Editor* m_editor;
		LayerList m_layers;

	public:
		static Engine* get();
		static Window* get_window();
		static Renderer* get_renderer();
		static ResourceManager* get_resources();
	};
}
