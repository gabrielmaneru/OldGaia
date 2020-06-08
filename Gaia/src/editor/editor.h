#pragma once
namespace Gaia {
	class ImGuiLayer;

	class Editor {
	public:
		Editor();
		~Editor();

		void render();

	private:
		ImGuiLayer* m_layer; // Borrowed ownership
	};
}