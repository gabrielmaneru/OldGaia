#include "gaia_pch.h"
#include "event_handler.h"
#include "event_dispatcher.h"

namespace Gaia{
	EventHandler::~EventHandler()
	{
		for (auto& it : collection)
		{
			EventDispatcher::unsubscribe(*this, it.first);
			delete it.second;
		}
	}

	void EventHandler::handle_event(const iEvent & event)
	{
		//Tries to find the event in the Map
		auto search = collection.find(type_of(event));

		if (search != collection.end())
			search->second->handle(event);
	}
}