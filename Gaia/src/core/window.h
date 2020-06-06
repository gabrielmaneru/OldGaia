#pragma once
namespace Gaia {
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void setup() = 0;
		virtual void update() = 0;
		virtual const std::string& get_title()const = 0;
		virtual urect get_canvas()const = 0;
		virtual void* get_native()const = 0;
		virtual bool get_minimized()const = 0;
		virtual bool get_vsync()const = 0;

		static Window* create(const std::string & title, urect canvas);
	};
}