#pragma once
#include "type_info.h"
#include "event_interfaces.h"
#include "event_dispatcher.h"

#include <map>

namespace Gaia {
	// Handle for registering events on EventHandlers
	template<class T, class EVENT>
	class MemberFunctionHandler : public iHandler
	{
		typedef void(T::*Member)(const EVENT &);
	public:
		MemberFunctionHandler(T * o, Member f)
			: obj(o), fn(f) {}
		void call(const iEvent & event)
		{
			(obj->*fn)(static_cast<const EVENT &>(event));
		}

	private:
		T * obj;
		Member fn;
	};

	// Listener and handler of the event
	class EventHandler : public iListener
	{
	public:
		virtual ~EventHandler();

		template<class T, class EVENT>
		void register_event(T & listener, void(T::*MemberFunction)(const EVENT &))
		{
			EventDispatcher::subscribe(listener, TypeInfo(typeid(EVENT)));
			register_handler(listener, MemberFunction);
		}


	private:
		void handle_event(const iEvent &)override;
		template<class T, class EVENT>
		void register_handler(T & listener, void(T::*MemberFunction)(const EVENT &))
		{
			if (collection[TypeInfo(typeid(EVENT))] == 0)
				collection[TypeInfo(typeid(EVENT))] = new MemberFunctionHandler<T, EVENT>(&listener, MemberFunction);
		}
		std::map<TypeInfo, iHandler*> collection;
	};
}