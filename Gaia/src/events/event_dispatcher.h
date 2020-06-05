#pragma once
#include "type_info.h"
#include "event_interfaces.h"

#include <map>
#include <vector>

namespace Gaia{
	class EventDispatcher
	{
	public:
		void subscribe(iListener &, TypeInfo);
		void unsubscribe(iListener &, TypeInfo);
		void trigger_event(const iEvent &)const;
		friend void trigger_event(const iEvent&);

	private:
		EventDispatcher() = default;
		std::map<TypeInfo, std::vector<iListener*> > m_listeners;
	};
	void trigger_event(const iEvent&);
}