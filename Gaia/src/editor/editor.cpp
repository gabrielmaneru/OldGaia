#include "gaia_pch.h"
#include "editor.h"
#include <core/engine.h>

#include <imgui/imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <extern/ImGui/ImGuizmo.h>
#include <GLFW/glfw3.h>

#pragma warning(disable : 4312) // conversion of different size from u32 to void*

namespace Gaia {
	Editor::Editor()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Configuration
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImFont* pFont = io.Fonts->AddFontFromFileTTF("assets/fonts/NotoSans-Regular.ttf", 20.0f);
		io.FontDefault = io.Fonts->Fonts.back();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, style.Colors[ImGuiCol_WindowBg].w);

		GLFWwindow* window = static_cast<GLFWwindow*>(s_window->get_native());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		ImGuizmo::SetOrthographic(false);
		
		m_windows.emplace_back(EditorWindow{ true, "Viewport", fn_viewport });
		m_windows.emplace_back(EditorWindow{ true, "Hierarchy", fn_hierarchy });
		m_windows.emplace_back(EditorWindow{ true, "Inspector", fn_inspector });
	}
	Editor::~Editor()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void Editor::render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//TODO ImGuizmo::BeginFrame();
		//ImGui::ShowDemoWindow();

		render_docking();

		ImGuiIO& io = ImGui::GetIO();
		urect canvas = s_window->get_canvas();
		io.DisplaySize = ImVec2((float)canvas.x, (float)canvas.y);

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	void Editor::render_docking()
	{
		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace GUI", 0, window_flags);
		ImGui::PopStyleVar(3);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),
				ImGuiDockNodeFlags_None);
		}

		// Render Menu Bar
		if (ImGui::BeginMenuBar())
		{
			// General File Menu
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::Button("Exit"))
					s_engine->stop_execution();
				ImGui::EndMenu();
			}

			// Open/Close Window
			if (ImGui::BeginMenu("Window"))
			{
				for (auto& w : m_windows)
					ImGui::Checkbox(w.name, &w.open);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::ShowDemoWindow();
		// Render every window
		for (auto& w : m_windows)
			if (w.open)
			{
				if (ImGui::Begin(w.name, &w.open))
					w.fn(this);
				ImGui::End();
			}
		ImGui::End();
	}
	void fn_viewport(Editor * editor)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImVec2 windowSize = ImGui::GetContentRegionAvail();
		ImVec2 windowPos = ImGui::GetWindowPos();
		urect rect_win = { (u32)windowSize.x, (u32)windowSize.y };
		s_renderer->set_viewport(rect_win);

		ImGui::Image((ImTextureID)s_renderer->get_final_texture_id(0), windowSize, { 0, 1 }, { 1, 0 });
		ImGui::Separator();
		ImGui::Image((ImTextureID)s_renderer->get_final_texture_id(1), windowSize, { 0, 1 }, { 1, 0 });
		ImGui::Separator();
		ImGui::Image((ImTextureID)s_renderer->get_final_texture_id(2), windowSize, { 0, 1 }, { 1, 0 });
		ImGui::Separator();
		ImGui::Image((ImTextureID)s_renderer->get_final_texture_id(3), windowSize, { 0, 1 }, { 1, 0 });


		// Gizmos
		auto scn = s_session->get_current_scene();
		auto selected = scn->m_selected;
		if (/*m_GizmoType != -1 &&*/ selected)
		{
			static ImGuizmo::OPERATION m_operation{ ImGuizmo::TRANSLATE };
			if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
			{
				//if (input.is_key_triggered(GLFW_KEY_1))
				//	m_operation = ImGuizmo::TRANSLATE;
				//if (input.is_key_triggered(GLFW_KEY_2))
				//	m_operation = ImGuizmo::ROTATE;
			}
			auto cam = s_session->get_active_camera();
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);
			ImGuizmo::Manipulate(
				&cam->get_view()[0][0],
				&cam->get_projection(rect_win)[0][0],
				m_operation, ImGuizmo::WORLD,
				&selected->get_matrix()[0][0], NULL, NULL);
		}
		ImGui::PopStyleVar();
	}
	void fn_hierarchy(Editor * editor)
	{
		auto scn = s_session->get_current_scene();
		auto lvl = scn->get_level();
		std::string name{"Scene: "};
		if (lvl) name += lvl->get_name();
		else name += "Unnamed";

		if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			auto entities = scn->get_entities();
			for (auto& e : entities)
				if (ImGui::Selectable(e->get_name().c_str(), e == scn->m_selected))
					scn->m_selected = e;
			ImGui::TreePop();
		}
	}
	void fn_inspector(Editor * editor)
	{
		auto scn = s_session->get_current_scene();
		if (scn->m_selected)
		{
			auto e = scn->m_selected;

			char buf[100];
			strcpy(buf, e->get_name().c_str());
			ImGui::Text("Name");
			ImGui::SameLine();
			if(ImGui::InputText("##hide_label", buf, 100))
				e->set_name(buf);
			ImGui::Separator();
			if (ImGui::TreeNode("Transform"))
			{
				ImGui::InputFloat3("Position", &e->get_position()[0]);
				if (ImGui::InputFloat4("Rotation", &e->get_rotation()[0]))
					e->get_rotation() = glm::normalize(e->get_rotation());
				ImGui::InputFloat3("Scale", &e->get_scale()[0]);
				ImGui::TreePop();
			}

			auto cmps = e->get_component_map();
			for (auto& c : cmps)
				if (ImGui::TreeNode(c.second->get_type_name().c_str()))
				{
					c.second->render_editor();
					ImGui::TreePop();
				}
		}
	}
	bool insert_name(char * buf, u32 buf_size)
	{
		bool save = false;
		if (ImGui::BeginPopupModal("insert_name"))
		{
			ImGui::Text("Name: ");
			ImGui::SameLine();
			ImGui::InputText("##hide_label", buf, buf_size);
			ImGui::Separator();
			if (ImGui::Button("Save"))
				ImGui::CloseCurrentPopup(), save = true;
			ImGui::SameLine();
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}
		return save;
	}
	void select_material(shared<Material>& material_slot)
	{
		if (ImGui::BeginPopup("select_material"))
		{
			static ImGuiTextFilter filter;
			filter.Draw();
			ImGui::SameLine();
			static char buf[100];
			if (ImGui::Button("Add"))
				ImGui::OpenPopup("insert_name"), memset(buf, 0, sizeof(buf));
			
			if (insert_name(buf, 100))
				Material::create(buf);


			auto map = s_resources->get_map<Material>();
			for (auto& key : map)
				if (filter.PassFilter(key.first.c_str()))
					if (ImGui::Selectable(key.first.c_str(),
						material_slot? key.first==material_slot->get_name():false))
						material_slot = s_resources->get<Material>(key.first.c_str());
			ImGui::EndPopup();
		}
	}
	void select_texture(shared<Texture2D>& texture_slot)
	{
		if (ImGui::BeginPopup("select_texture"))
		{
			static ImGuiTextFilter filter;
			filter.Draw();
			auto map = s_resources->get_map<Texture2D>();
			for (auto& key : map)
				if (filter.PassFilter(key.first.c_str()))
					if (ImGui::Selectable(key.first.c_str(),
						texture_slot ? key.first == texture_slot->get_name() : false))
						texture_slot = s_resources->get<Texture2D>(key.first.c_str());
			ImGui::EndPopup();
		}
	}
	void edit_material(shared<Material>& material_slot)
	{
		if (ImGui::BeginPopupModal("edit_material"))
		{
			ImGui::Text("Material: "); ImGui::SameLine();
			ImGui::Text(material_slot->get_name().c_str());
			ImGui::Separator();

			static int slot = 0;
			auto show = [](shared<Texture2D>& txt, int slot_)
			{
				ImGui::PushID(slot_);
				std::string name;
				if (txt)
					name = txt->get_name();
				else
					name = "...";
				if (ImGui::Button(name.c_str()))
					ImGui::OpenPopup("select_texture"), slot = slot_;
				ImGui::PopID();
			};
			{
				ImGui::Checkbox("Albedo", &material_slot->m_texture_active[0]);
				ImGui::SameLine();
				if (material_slot->m_texture_active[0])
					show(material_slot->m_albedo_texture, 0);
				else
					ImGui::ColorEdit3("##hide_label", &material_slot->m_albedo_color.x);
			}
			{
				ImGui::Checkbox("Metallic", &material_slot->m_texture_active[1]);
				ImGui::SameLine();
				if (material_slot->m_texture_active[1])
					show(material_slot->m_metallic_texture, 1);
				else
					ImGui::SliderFloat("##hide_label", &material_slot->m_metallic_color, 0.f, 1.f);
			}
			{
				ImGui::Checkbox("Roughness", &material_slot->m_texture_active[2]);
				ImGui::SameLine();
				if (material_slot->m_texture_active[2])
					show(material_slot->m_roughness_texture, 2);
				else
					ImGui::SliderFloat("##hide_label", &material_slot->m_roughness_color, 0.0f, 1.0f);
			}
			{
				ImGui::Checkbox("Normal", &material_slot->m_texture_active[3]);
				ImGui::SameLine();
				if (material_slot->m_texture_active[3])
					show(material_slot->m_normal_texture, 3);
			}
			ImGui::PushID(slot);
			switch (slot)
			{
			case 0:
				select_texture(material_slot->m_albedo_texture);
				break;
			case 1:
				select_texture(material_slot->m_metallic_texture);
				break;
			case 2:
				select_texture(material_slot->m_roughness_texture);
				break;
			case 3:
				select_texture(material_slot->m_normal_texture);
				break;
			}
			ImGui::PopID();

			ImGui::NewLine();
			if (ImGui::Button("Save", ImVec2(120, 0)))
				ImGui::CloseCurrentPopup(), material_slot->save_material();

			ImGui::EndPopup();
		}
	}
}
