#include <gaia.h>
#include <core/entry_point.h>

#include "sandbox_layer.h"


class Sandbox : public Gaia::Engine {
public:
	Sandbox::Sandbox() {
		GAIA_LOG_TRACE("Sandbox Program Start");
		std::shared_ptr<SandboxLayer> p(new SandboxLayer());
		m_sandbox = p;
		Engine::get()->add_layer(std::move(p));
	}
	Sandbox::~Sandbox() {
		GAIA_LOG_TRACE("Sandbox Program End");
	}

private:
	std::weak_ptr<SandboxLayer> m_sandbox;
};

Gaia::Engine* Gaia::create_program() {
	static Sandbox* instance = new Sandbox();
	return instance;
}
