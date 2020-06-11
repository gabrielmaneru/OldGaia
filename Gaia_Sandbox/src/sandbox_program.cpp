#include <gaia.h>
#include <core/entry_point.h>

#include "sandbox_layer.h"


class Sandbox : public Gaia::Engine {
public:
	Sandbox::Sandbox() {
		Engine::get()->add_layer(std::make_shared<SandboxLayer>());
	}
};

Gaia::Engine* Gaia::create_program() {
	static Sandbox* instance = new Sandbox();
	return instance;
}
