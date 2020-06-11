#include "gaia_pch.h"
#include "renderable.h"
#include <core/engine.h>
#include <renderer/renderer.h>

namespace Gaia {
	Renderable::Renderable()
	{
		Engine::get_renderer()->register_renderable(this);
	}

	Renderable::~Renderable()
	{
		Engine::get_renderer()->unregister_renderable(this);
	}
}
