/**
\class EventSubclass sub-class
*/

#pragma once

#include "Event/Event.h"
#include <sstream>

namespace Engine
{

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		static EventType getStaticType() { return EventType::WindowClose; }

		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
		//inline const char* GetName() const override {}
	};

	class WindowResizeEvent : public Event
	{
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}

		static EventType getStaticType() { return EventType::WindowResize; }

		virtual EventType getEventType() const override { return EventType::WindowResize; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
		//inline const char* GetName() const override { return; }
	};

	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	//////////////////////////////////////////

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EventType KeyPressed();
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EventType KeyReleased();
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EventType KeyTyped();
	};

	

	class WindowMoved : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowMoved; }

		EventType getEventType() const override { return EventType::WindowMoved; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class KeyPressed : public Event
	{
	private:
		int m_keycode;
		int m_repeatCount;
	public:
		KeyPressed(int keycode, int repeatCount) : m_keycode(keycode), m_repeatCount(repeatCount) {}
		static EventType getStaticType() { return EventType::KeyPressed; }

		EventType getEventType() const override { return EventType::KeyPressed; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeycode() const { return m_keycode; }
		inline int getRepeatCount() const { return m_repeatCount; }
	};

	class KeyReleased : public Event
	{
	private:
		int m_keycode;
	public:
		KeyReleased(int keycode) : m_keycode(keycode) {}
		static EventType getStaticType() { return EventType::KeyReleased; }

		EventType getEventType() const override { return EventType::KeyReleased; }
		int getCategoryFlags() const override { return EventCategoryKeyboard; }

		inline int getKeycode() const { return m_keycode; }
	};

	class KeyTyped : public Event
	{
	private:
		int m_keycode;
	public:
		KeyTyped(int keycode) : m_keycode(keycode) {}
		static EventType getStaticType() { return EventType::KeyTyped; }

		EventType getEventType() const override { return EventType::KeyTyped; }
		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

		inline int getKeycode() const { return m_keycode; }
	};

	class MouseButtonPressed : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonPressed(int button) : m_button(button) {}
		static EventType getStaticType() { return EventType::MouseButtonPressed; }

		EventType getEventType() const override { return EventType::MouseButtonPressed; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }
		
		inline int getButton() const { return m_button; }
	};

	class MouseButtonReleased : public Event
	{
	private:
		int m_button;
	public:
		MouseButtonReleased(int button) : m_button(button) {}
		static EventType getStaticType() { return EventType::MouseButtonReleased; }

		EventType getEventType() const override { return EventType::MouseButtonReleased; }
		int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getButton() const { return m_button; }
	};

	class MouseMoved : public Event
	{
	private:
		float m_offsetX;
		float m_offsetY;
	public:
		MouseMoved(int offsetX, int offsetY) : m_offsetX(offsetX), m_offsetY(offsetY) {}
		static EventType getStaticType() { return EventType::MouseMoved; }

		EventType getEventType() const override { return EventType::MouseMoved; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getoffsetX() const { return m_offsetX; }
		inline int getoffsetY() const { return m_offsetY; }
	};

	class MouseScrolled : public Event
	{
	private:
		float m_offsetX;
		float m_offsetY;
	public:
		MouseScrolled(int offsetX, int offsetY) : m_offsetX(offsetX), m_offsetY(offsetY) {}
		static EventType getStaticType() { return EventType::MouseScrolled; }

		EventType getEventType() const override { return EventType::MouseScrolled; }
		int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getoffsetX() const { return m_offsetX; }
		inline int getoffsetY() const { return m_offsetY; }
	};
}