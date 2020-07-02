#pragma once
namespace Gaia {
	class ImGuiLayer;
	class Editor;

	struct EditorWindow
	{
		typedef void(*WindowFunc)(Editor*);

		bool open;
		const char* name;
		WindowFunc fn;
	};

	class Editor {
	public:
		Editor();
		~Editor();

		void render();

	private:
		void render_docking();
		std::vector<EditorWindow> m_windows;
	};
	void fn_viewport(Editor* editor);
	void fn_hierarchy(Editor* editor);
	void fn_inspector(Editor* editor);
}