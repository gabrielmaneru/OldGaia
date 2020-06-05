#include "gaia_pch.h"
#include "engine.h"
namespace Gaia {
	Engine::Engine()
	{
		GAIA_ELOG_TRACE("Gaia Started")
		// Check is application already exists
		static Engine* instance = nullptr;
		assert(instance == nullptr);
		instance = this;

		// Create window
		m_window = Window::create("\"Gaia Engine\"", {1280, 720});

	}

	Engine::~Engine()
	{
		GAIA_ELOG_TRACE("Gaia Ended")
	}

	void Engine::run()
	{
		int i = 0;
		while (i++< 60)
		{
			m_window->update();
		}
	}
}
