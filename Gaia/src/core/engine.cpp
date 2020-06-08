#include "gaia_pch.h"
#include "engine.h"

namespace Gaia {
	Engine * instance = nullptr;

	Engine::Engine()
		:m_running(true){
		// Check if application already exists
		GAIA_EASSERT(!instance, "Engine already created!");
		instance = this;

		GAIA_ELOG_TRACE("Engine Initializing");
		{
			// Create window
			m_window = new Window{ "Gaia Engine", {1280, 720} };
			register_event(*this, &Engine::on_window_close);
			m_window->set_vsync(true);

			// Create renderer
			m_renderer = new Renderer();

			// Create editor
			m_editor = new Editor{};
		}
		GAIA_ELOG_TRACE("Engine Initialize Succesfully"); std::cout << std::endl;
	}

	Engine::~Engine(){

		m_layers.clear();

		delete m_editor;
		delete m_renderer;
		delete m_window;
	}

	void Engine::run(){
		while (m_running){
			if (!m_window->get_minimized())
			{
				m_renderer->render();
				m_editor->render();
			}
			m_window->update();
		}
	}

	void Engine::run_layers(std::function<void(std::shared_ptr<Layer>)> func)
	{
		for (auto l : m_layers)
			func(l);
	}

	void Engine::on_window_close(const WindowClose_Event & event){
		m_running = false;
	}
	Engine * Engine::get()
	{
		GAIA_EASSERT(instance, "Invalid Engine Access");
		return instance;
	}
	Window * Engine::get_window()
	{
		Window* w = get()->m_window;
		GAIA_EASSERT(w, "Invalid Window Access");
		return w;
	}
	Renderer * Engine::get_renderer()
	{
		Renderer* w = get()->m_renderer;
		GAIA_EASSERT(w, "Invalid Window Access");
		return w;
	}
}
