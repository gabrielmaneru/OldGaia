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
		void render_viewport();
		void render_hierarchy();
		void render_inspector();

		bool m_viewport{ true };
		bool m_hierarchy{ true };
		bool m_inspector{ true };
	};
}