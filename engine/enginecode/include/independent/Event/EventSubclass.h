/**
\class EventSubclass sub-class
*/

#pragma once

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

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}

	EventType getEventType() const override { return EventType::WindowClose; }
	int getCategoryFlags() const override { return EventCategoryWindow;  }
};

class WindowResizeEvent : public Event
{
private:
	int m_width;
	int m_height;
public:
	WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}

	EventType getEventType() const override { return EventType::WindowResize; }
	int getCategoryFlags() const override { return EventCategoryWindow; }

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
};

