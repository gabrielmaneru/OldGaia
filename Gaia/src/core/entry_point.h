#pragma once

namespace Gaia {
	extern Engine* create_program();
}

int main(int argc, char ** argv)
{
	Gaia::Log::Init();

	auto program = Gaia::create_program();
	program->run();
	delete program;
}