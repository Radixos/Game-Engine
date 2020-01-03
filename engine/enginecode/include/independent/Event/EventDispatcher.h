/**
\class EventDispatcher class
*/

#pragma once

#include "Event/Event.h"

namespace Engine {

	class EventDispatcher
	{
		template<typename T>	//!<Template for EventDispatcher
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_event(event)	//!<EventDispatcher constructor
		{
			//Should there be anuthing here??
		}

		template<typename T>	//!<Template for EventDispatcher
		bool dispatch(EventFunc<T> func)	//!<Dispatch function
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

}