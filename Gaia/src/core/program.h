#pragma once
#include "gaia_pch.h"
#include "window.h"

namespace Gaia {
	class Program
	{
	public:
		Program();
		virtual void run()final;
		virtual ~Program();
		
	private:
		Unique<Window> m_window;
	};
}

#define Program_API(program)\
class program : public Gaia::Program\
{public:program();~program();};\
Gaia::Program* Gaia::create_program()\
{static program* instance = new program(); return instance;}