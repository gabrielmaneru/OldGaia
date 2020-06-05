#pragma once
#include "type_info.h"
#include "event_interfaces.h"

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
		void register_handler(T & listener, void(T::*MemberFunction)(const EVENT &))
		{
			if (collection[TypeInfo(typeid(EVENT))] == 0)
				collection[TypeInfo(typeid(EVENT))] = new MemberFunctionHandler<T, EVENT>(&listener, MemberFunction);
		}

		void handle(const iEvent &);

	private:
		std::map<TypeInfo, iHandler*> collection;
	};
}