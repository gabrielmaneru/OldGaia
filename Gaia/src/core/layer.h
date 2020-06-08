#pragma once
#include <events/event_listener.h>

namespace Gaia {
	class Layer	: public EventListener {
	public:
		Layer(const std::string& name)
			: m_name(name) {}
		virtual ~Layer()=default;

		virtual void begin() {};
		virtual void update() {};
		virtual void render_editor() {};
		virtual void end() {};

	protected:
		std::string m_name;
	};
	using LayerList = std::list< std::shared_ptr<Layer> >;
}