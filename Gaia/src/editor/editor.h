#pragma once
namespace Gaia {
	class ImGuiLayer;

	class Editor {
	public:
		Editor();
		~Editor();

		void render();

	private:
		std::weak_ptr<ImGuiLayer> m_layer; // Borrowed ownership
	};
}