#pragma once
#include <renderer/material.h>
#include <renderer/texture2D.h>

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
	void fn_render_buffers(Editor* editor);

	bool insert_name(char* buf, u32 buf_size);
	void select_material(shared<Material>& material_slot);
	void select_texture(shared<Texture2D>& texture_slot);
	void edit_material(shared<Material>& material_slot);
}