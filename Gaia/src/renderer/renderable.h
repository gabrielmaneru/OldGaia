#pragma once
#include <renderer/shader.h>

namespace Gaia {
	class Renderable {
	public:
		void register_renderable();
		void unregister_renderable();
		virtual ~Renderable()=default;
		virtual void draw(Shader * shader)const = 0;
	};
}