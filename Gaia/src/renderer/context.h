#pragma once

struct GLFWwindow;
namespace Gaia {
	class Context {
	public:
		Context(GLFWwindow* native);
		void swap_buffers()const;

	private:
		GLFWwindow* m_native;
	};
}