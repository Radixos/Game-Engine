/**
\class Event base class
*/

#pragma once

//#include "engine.h"
#include <functional>
#include <iostream>

namespace Engine
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,		// 00000001
		EventCategoryInput = 1 << 1,		// 00000010
		EventCategoryKeyboard = 1 << 2,		// 00000100
		EventCategoryMouse = 1 << 3,		// 00001000
		EventCategoryMouseButton = 1 << 4	// 00010000
	};

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

}