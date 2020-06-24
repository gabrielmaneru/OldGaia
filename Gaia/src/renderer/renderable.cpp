#include "gaia_pch.h"
#include "renderable.h"
#include <core/engine.h>
#include <renderer/renderer.h>

namespace Gaia {
	void Renderable::register_renderable()
	{
		Engine::get_renderer()->register_renderable(this);
	}
	void Renderable::unregister_renderable()
	{
		Engine::get_renderer()->unregister_renderable(this);
	}
}
