#pragma once
#include <core/layer.h>

namespace Gaia {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer()
			: Layer("ImGui") {}
		virtual ~ImGuiLayer() = default;

		void begin()override;
		void render_editor()override;
		void end()override;

		void render_begin();
		void render_end();
	};
}