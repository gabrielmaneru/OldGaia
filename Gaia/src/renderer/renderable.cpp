#include "gaia_pch.h"
#include "renderable.h"
#include <core/engine.h>
#include <renderer/renderer.h>

namespace Gaia {
	void Renderable::register_renderable()
	{
		s_renderer->register_renderable(this);
	}
	void Renderable::unregister_renderable()
	{
		s_renderer->unregister_renderable(this);
	}
}
