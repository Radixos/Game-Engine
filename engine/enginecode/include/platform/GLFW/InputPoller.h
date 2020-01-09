/**
\class InputPoller class
*/

#pragma once
#include <glm/glm.hpp>

namespace Engine {

	class InputPoller
	{
	private:
		static InputPoller* s_instance; //!<Single instance pointer - singleton (internal implementation)
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0; //!<Windows API specific implementation of key press
		virtual bool isMouseButtonPressedImpl(int button) = 0; //!<Windows API specific implementation of mouse button press
		virtual glm::vec2 getMousePositionImpl() = 0; //!< Windows API specific implementation of mouse position
		virtual float getMouseXImpl() = 0; //!<Windows API specific implementation of mouse x position
		virtual float getMouseYImpl() = 0; //!<Windows API specific implementation of mouse y position
	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); } //!<Is the key with this keycode pressed
		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); } //!<Is this mouse button pressed
		inline static glm::vec2 getMousePosition() { return s_instance->getMousePositionImpl(); } //!<Get the current position of the mouse
		inline static float getMouseX() { return s_instance->getMouseXImpl(); } //!<Get the current x position of the mouse
		inline static float getMouseY() { return s_instance->getMouseYImpl(); } //!<Get the current y position of the mouse
	};
}