#include "gaia_pch.h"
#include "engine.h"

#include <GLFW/glfw3.h>

namespace Gaia {

	Engine* s_engine = nullptr;
	Window* s_window = nullptr;
	Renderer* s_renderer = nullptr;

	Engine::Engine()
		:m_running(true) {
		// Check if application already exists
		GAIA_EASSERT(!s_engine, "Engine already created!");
		s_engine = this;

		GAIA_ELOG_TRACE("Engine Initializing");{
			// Create window
			s_window = new Window{ "Gaia Engine", {1280, 720} };
			register_event(*this, &Engine::on_window_close);
			s_window->set_vsync(true);
			// Create renderer
			s_renderer = new Renderer();

			// Create session
			m_session = new Session();
		}
		GAIA_ELOG_TRACE("Engine Initialized Succesfully"); std::cout << std::endl;
	}

	Engine::~Engine(){
		delete m_session;

		delete s_renderer;
		delete s_window;
	}

	void Engine::run(){
		m_session->begin();
		while (m_running){
			if (!s_window->get_minimized())
			{
				m_session->update(m_timestep);
				s_renderer->render();
				m_session->render_editor();
			}
			s_window->update();
			float time = (float)glfwGetTime();
			m_timestep = time - m_last_frametime;
			m_last_frametime = time;
		}
		m_session->end();
	}

	void Engine::stop_execution()
	{
		m_running = false;
	}

	void Engine::on_window_close(const WindowClose_Event & event){
		m_running = false;
	}
}
