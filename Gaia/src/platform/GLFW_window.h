#pragma once
#include "gaia_pch.h"
#include <core/window.h>

#include <GLFW/glfw3.h>

namespace Gaia {
	class GLFW_window : public Window
	{
	public:
		GLFW_window(const std::string & title, urect canvas);
		virtual ~GLFW_window();

		void update() override;
		const std::string& get_title() const override { return m_title; };
		urect              get_canvas()const override { return m_canvas; };
		void*              get_native()const override { return m_native; };

	private:
		std::string m_title;
		urect m_canvas;
		GLFWwindow* m_native;
	};
}