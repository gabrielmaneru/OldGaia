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

			// Create editor
			m_editor = new Editor{};
		}
		GAIA_ELOG_TRACE("Engine Initialize Succesfully");
	}

	Engine::~Engine(){

		m_layers.clear();

		delete m_editor;
		delete m_window;
	}

	void Engine::run(){
		while (m_running){
			if (!m_window->get_minimized())
			{
				m_editor->render();
			}
			m_window->update();
		}
	}
	Engine * Engine::get() {
		return instance;
	}

	void Engine::on_window_close(const WindowClose_Event & event){
		m_running = false;
	}
}
