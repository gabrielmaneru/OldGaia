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

		ImFont* pFont = io.Fonts->AddFontFromFileTTF("assets/fonts/NotoSans-Regular.ttf", 24.0f);
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
		ImGui::Image((ImTextureID)s_renderer->get_final_texture_id(), windowSize, { 0, 1 }, { 1, 0 });


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
}
