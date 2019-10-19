/**
\class Event dispatcher
*/

#pragma once

#include "Event/Event.h"

class EventDispatcher
{
	template<typename T>
	using EventFunc = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event) : m_event(event)
	{

	}

	template<typename T>
	bool dispatch(EventFunc<T> func)
	{
		if (m_event.getEventType() == T::getStaticType())
		{
			m_event.handle(func(*((t*)&m_event)));
			return true;
		}
		return false;
	}
private:
	Event& m_event;
};