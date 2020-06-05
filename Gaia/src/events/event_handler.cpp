#include "gaia_pch.h"
#include "event_handler.h"
namespace Gaia{
	EventHandler::~EventHandler()
	{
		for (auto& it : collection)
			delete it.second;
	}

	void EventHandler::handle(const iEvent & event)
	{
		//Tries to find the event in the Map
		auto search = collection.find(type_of(event));

		if (search != collection.end())
			search->second->handle(event);
	}
}