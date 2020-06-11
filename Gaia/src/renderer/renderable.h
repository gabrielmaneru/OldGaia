#pragma once
namespace Gaia {
	class Renderable {
	public:
		Renderable();
		virtual ~Renderable();
		virtual void draw()const = 0;
	};
}