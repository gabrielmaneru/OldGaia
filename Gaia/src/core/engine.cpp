#include "gaia_pch.h"
#include "engine.h"
namespace Gaia {
	Engine::Engine()
	{
		// Check is application already exists
		static Engine* instance = nullptr;
		GAIA_EASSERT(!instance, "Engine already created!");
		instance = this;
		GAIA_ELOG_TRACE("Gaia Started")

		// Create window
		m_window = Window::create("Gaia Engine", {1280, 720});
		m_window->setup();

	}

	Engine::~Engine()
	{
		GAIA_ELOG_TRACE("Gaia Ended")
	}

	void Engine::run()
	{
		int i = 0;
		while (i++< 60000)
		{
			m_window->update();
		}
	}
}
