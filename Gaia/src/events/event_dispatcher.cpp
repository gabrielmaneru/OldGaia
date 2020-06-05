#include "gaia_pch.h"
#include "event_dispatcher.h"
namespace Gaia {
	void EventDispatcher::subscribe(iListener & listener, TypeInfo type)
	{
		m_listeners[type].push_back(&listener);
	}

	void EventDispatcher::unsubscribe(iListener & listener, TypeInfo type)
	{
		//Tries to find the event in the Map
		auto it = m_listeners.find(type);
		if (it == m_listeners.end())
			return;

		//Search the Listener and erase it
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			if (it->second[i] == &listener)
			{
				it->second.erase(it->second.begin() + i);
			}
		}
	}

	void EventDispatcher::trigger_event(const iEvent & event)const
	{
		//Tries to find the event in the Map
		std::map<TypeInfo, std::vector<iListener*> >::const_iterator it = m_listeners.find(type_of(event));

		if (it != m_listeners.cend())
		{
			//handle the event for each Listener
			for (unsigned i = 0; i < it->second.size(); i++)
			{
				it->second[i]->handle_event(event);
			}
		}
	}
	void trigger_event(const iEvent& e)
	{
		static EventDispatcher disp;
		disp.trigger_event(e);
	}
}