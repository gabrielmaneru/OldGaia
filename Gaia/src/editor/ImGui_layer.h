#pragma once
#include <core/layer.h>

namespace Gaia {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void render_begin();
		void render_editor()override;
		void render_end();
	};
}