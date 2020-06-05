#include <gaia.h>
#include <core/entry_point.h>

Gaia_API(Sandbox)

Sandbox::Sandbox()
{
	GAIA_CLIENT_TRACE("Sandbox Program Start");
}

Sandbox::~Sandbox()
{
	GAIA_CLIENT_TRACE("Sandbox Program End");
}