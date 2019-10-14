/**
\class Event base class
*/

#pragma once

//#include "engine.h"
#include "EventSubclass.h"
#include <functional>
#include <iostream>

class Event
{
private:
	bool m_handled = false;
public:
	virtual EventType getEventType() const = 0;	//!< Get the event type
	virtual int getCategoryFlags() const = 0;	//!< Get the event category
	inline bool handled() const { return m_handled; }	//!< Has the event been handled
	inline void handle(bool isHandled) { m_handled = isHandled; }	//!< Handle the event
	inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }	//!< Is this event in the category?
};