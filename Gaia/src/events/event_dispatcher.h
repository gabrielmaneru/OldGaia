#pragma once
#include "type_info.h"
#include "event_interfaces.h"

#include <map>
#include <vector>

namespace Gaia{
	class EventDispatcher
	{
	public:
		static void trigger_event(const iEvent &);

	private:
		friend class EventHandler;
		static void subscribe(iListener &, TypeInfo);
		static void unsubscribe(iListener &, TypeInfo);
		static EventDispatcher instance;
		EventDispatcher() = default;
		std::map<TypeInfo, std::vector<iListener*> > m_listeners;
	};
}