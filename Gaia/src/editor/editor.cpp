#include "gaia_pch.h"
#include "editor.h"
#include <core/engine.h>
#include <editor/ImGui_layer.h>

namespace Gaia {
	Editor::Editor()
	{
		m_layer = new ImGuiLayer();
		// Transfer Ownership
		Engine::get()->add_layer(m_layer);
	}
	Editor::~Editor()
	{
		m_layer = nullptr;
	}
	void Editor::render()
	{
		m_layer->render_begin();

		//auto layers = Engine::get()->get_layers();
		//for (auto it = layers.begin(); it != layers.end(); it++)
		//	(*it)->render_editor();

		m_layer->render_end();
	}
}
