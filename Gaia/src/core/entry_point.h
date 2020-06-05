#pragma once

namespace Gaia {
	extern Program* create_program();
}

int main(int argc, char ** argv)
{
	auto program = Gaia::create_program();
	program->run();
	delete program;
}