#pragma once
#include "gaia_pch.h"
#include "window.h"

namespace Gaia {
	class Engine
	{
	public:
		Engine();
		virtual void run()final;
		virtual ~Engine();
		
	private:
		Window* m_window;
	};
}

#define Gaia_API(program)\
class program : public Gaia::Engine\
{public:program();~program();};\
Gaia::Engine* Gaia::create_program()\
{static program* instance = new program(); return instance;}