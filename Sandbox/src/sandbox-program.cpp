#include <gaia.h>

class Sandbox : public Gaia::Program
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Gaia::Program* Gaia::create_program()
{
	static Sandbox* instance = new Sandbox();
	return instance;
}