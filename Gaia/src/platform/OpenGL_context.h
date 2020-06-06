#pragma once
#include <renderer/context.h>

struct GLFWwindow;
namespace Gaia {
	class OpenGL_context : public Context
	{
	public:
		OpenGL_context(GLFWwindow* native);
		virtual void swap_buffers()override;
	private:
		GLFWwindow* m_native;
	};
}