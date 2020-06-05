#pragma once
namespace Gaia {
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void update() = 0;
		virtual const std::string& get_title()const = 0;
		virtual urect              get_canvas()const = 0;
		virtual void*              get_native()const = 0;

		static Unique<Window> create(const std::string & title, urect canvas);
	};
}