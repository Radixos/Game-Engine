/**
\class GLFWInputPoller.h base class
*/

#pragma once

#include "InputPoller.h"

namespace Engine {
	class GLFWInputPoller : public InputPoller
	{
	protected:
		bool isKeyPressedImpl(int keycode) override; //!<Windows API specific implementation of key press
		bool isMouseButtonPressedImpl(int button) override; //!<Windows API specific implementation of mouse button press
		glm::vec2 getMousePositionImpl() override; //!<Windows API specific implementation of mouse position
		float getMouseXImpl() override; //!<WIndows API specific implementation of mouse x position
		float getMouseYImpl() override; //!<WIndows API specific implementation of mouse y position
	};
}