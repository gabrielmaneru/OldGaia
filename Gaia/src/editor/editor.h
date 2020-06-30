#pragma once
namespace Gaia {
	class ImGuiLayer;

	class Editor {
	public:
		Editor();
		~Editor();

		void render();

	private:
		void render_docking();
	};
}