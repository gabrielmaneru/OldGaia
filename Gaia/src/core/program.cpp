#include "gaia_pch.h"
#include "program.h"
namespace Gaia {
	Program::Program()
	{
		// Check is application already exists
		static Program* instance = nullptr;
		assert(instance == nullptr);
		instance = this;

		// Create window
		m_window = Window::create("Gaia Engine", {1280, 720});

	}

	Program::~Program()
	{
	}

	void Program::run()
	{
		int i = 0;
		while (i++< 60)
		{
			m_window->update();
		}
	}
}
