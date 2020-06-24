#pragma once
namespace Gaia {
	class Renderable {
	public:
		void register_renderable();
		void unregister_renderable();
		virtual ~Renderable()=default;
		virtual void draw()const = 0;
	};
}