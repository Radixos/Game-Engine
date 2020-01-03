/**
\class EventSubclass sub-class
*/

#pragma once

#include "Event/Event.h"
#include <sstream>

namespace Engine
{
	class WindowCloseEvent : public Event	//!<WindowCloseEvent class publicly inhariting from Event
	{
	public:
		WindowCloseEvent() {}	//!<Constructor
		static EventType getStaticType() { return EventType::WindowClose; }

		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowResizeEvent : public Event	//!<WindowResizeEvent class publicly inhariting from Event
	{
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}	//!<Constructor
		static EventType getStaticType() { return EventType::WindowResize; }

		EventType getEventType() const override { return EventType::WindowResize; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};

	class WindowLostFocus : public Event	//!<WindowLostFocus class publicly inhariting from Event
	{
	private:
		float m_posX;
		float m_posY;
	public:
		WindowLostFocus(float posX, float posY) : m_posX(posX), m_posY(posY) {}	//!<Constructor
		static EventType getStaticType() { return EventType::WindowLostFocus; }

		EventType getEventType() const override { return EventType::WindowLostFocus; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

		inline float getposX() const { return m_posX; }
		inline float getposY() const { return m_posY; }
	};

	class WindowMoved : public Event	//!<WindowMoved class publicly inhariting from Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowMoved; }

		EventType getEventType() const override { return EventType::WindowMoved; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class KeyPressed : public Event	//!<KeyPressed class publicly inhariting from Event
	{
	private:
		int m_keycode;
		int m_repeatCount;
	public:
		KeyPressed(int keycode, int repeatCount) : m_keycode(keycode), m_repeatCount(repeatCount) {}	//!<Constructor
		static EventType getStaticType() { return EventType::KeyPressed; }

		EventType getEventType() const override { return EventType::KeyPressed; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeycode() const { return m_keycode; }
		inline int getRepeatCount() const { return m_repeatCount; }
	};

	class KeyReleased : public Event	//!<KeyReleased class publicly inhariting from Event
	{
	private:
		int m_keycode;
	public:
		KeyReleased(int keycode) : m_keycode(keycode) {}	//!<Constructor
		static EventType getStaticType() { return EventType::KeyReleased; }

		EventType getEventType() const override { return EventType::KeyReleased; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeycode() const { return m_keycode; }
	};

	class KeyTyped : public Event	//!<KeyTyped class publicly inhariting from Event
	{
	private:
		int m_keycode;
	public:
		KeyTyped(int keycode) : m_keycode(keycode) {}	//!<Constructor
		static EventType getStaticType() { return EventType::KeyTyped; }

		EventType getEventType() const override { return EventType::KeyTyped; }
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

		inline int getKeycode() const { return m_keycode; }
	};

	class MouseButtonPressed : public Event	//!<MouseButtonPressed class publicly inhariting from Event
	{
	private:
		int m_button;
	public:
		MouseButtonPressed(int button) : m_button(button) {}	//!<Constructor
		static EventType getStaticType() { return EventType::MouseButtonPressed; }

		EventType getEventType() const override { return EventType::MouseButtonPressed; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }
		
		inline int getButton() const { return m_button; }
	};

	class MouseButtonReleased : public Event	//!<MouseButtonReleased class publicly inhariting from Event
	{
	private:
		int m_button;
	public:
		MouseButtonReleased(int button) : m_button(button) {}	//!<Constructor
		static EventType getStaticType() { return EventType::MouseButtonReleased; }

		EventType getEventType() const override { return EventType::MouseButtonReleased; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getButton() const { return m_button; }
	};

	class MouseMoved : public Event	//!<MouseMoved class publicly inhariting from Event
	{
	private:
		float m_offsetX;
		float m_offsetY;
	public:
		MouseMoved(int offsetX, int offsetY) : m_offsetX(offsetX), m_offsetY(offsetY) {}	//!<Constructor
		static EventType getStaticType() { return EventType::MouseMoved; }

		EventType getEventType() const override { return EventType::MouseMoved; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getoffsetX() const { return m_offsetX; }
		inline int getoffsetY() const { return m_offsetY; }
	};

	class MouseScrolled : public Event	//!<MouseScrolled class publicly inhariting from Event
	{
	private:
		float m_offsetX;
		float m_offsetY;
	public:
		MouseScrolled(int offsetX, int offsetY) : m_offsetX(offsetX), m_offsetY(offsetY) {}	//!<Constructor
		static EventType getStaticType() { return EventType::MouseScrolled; }

		EventType getEventType() const override { return EventType::MouseScrolled; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getoffsetX() const { return m_offsetX; }
		inline int getoffsetY() const { return m_offsetY; }
	};
}