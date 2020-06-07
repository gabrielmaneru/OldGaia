#include <gaia.h>
#include <core/entry_point.h>


class Sandbox : public Gaia::Engine {
public:
	Sandbox::Sandbox() {
		GAIA_LOG_TRACE("Sandbox Program Start");
	}
	Sandbox::~Sandbox() {
		GAIA_LOG_TRACE("Sandbox Program End");
	}
};

Gaia::Engine* Gaia::create_program() {
	static Sandbox* instance = new Sandbox();
	return instance;
}
