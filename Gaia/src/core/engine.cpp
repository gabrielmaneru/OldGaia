#include "gaia_pch.h"
#include "engine.h"
namespace Gaia {
	Engine::Engine()
		:m_running(true){
		// Check if application already exists
		static Engine* instance = nullptr;
		GAIA_EASSERT(!instance, "Engine already created!");
		instance = this;

		// Create window
		m_window = new Window{ "Gaia Engine", {1280, 720} };
		// Register Window Resize Event
		register_event(*this, &Engine::on_window_close);
	}

	Engine::~Engine(){
		delete m_window;
	}

	void Engine::run(){
		while (m_running){
			m_window->update();
		}
	}

	void Engine::on_window_close(const WindowClose_Event & event){
		m_running = false;
	}
}
