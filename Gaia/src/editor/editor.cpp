#include "gaia_pch.h"
#include "editor.h"
#include <core/engine.h>
#include <editor/ImGui_layer.h>

namespace Gaia {
	Editor::Editor()
	{
		std::shared_ptr<ImGuiLayer> p(new ImGuiLayer());
		m_layer = std::weak_ptr(p);
		// Transfer Ownership to the engine
		Engine::get()->add_layer(std::move(p));
	}
	Editor::~Editor()
	{
	}
	void Editor::render()
	{
		if (auto p = m_layer.lock())
		{
			p->render_begin();
			Engine::get()->run_command(&Layer::render_editor);
			p->render_end();
		}
	}
}
