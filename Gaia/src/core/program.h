#pragma once
#include "target.h"

namespace Gaia {
	class Program
	{
	public:
		Program();
		virtual ~Program();
		void run();

	private:

	};
	Program * create_program();
}