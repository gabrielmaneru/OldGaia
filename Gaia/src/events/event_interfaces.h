#pragma once
#include "type_info.h"

namespace Gaia{
	// Event Interface
    class iEvent
    {
    public:
		virtual ~iEvent() = default;
    };

	// Handler Interface
    class iHandler
    {
    public:
		virtual ~iHandler() = default;
        virtual void call(const Gaia::iEvent &) = 0;
		virtual void handle(const iEvent & e) final { call(e); };
    };

	// Listener Interface
	class iListener
	{
	public:
		virtual ~iListener() = default;
	private:
		friend class EventDispatcher;
		virtual void handle_event(const iEvent &) = 0;
	};
}