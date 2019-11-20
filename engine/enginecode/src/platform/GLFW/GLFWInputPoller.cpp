/** \file GLFWInputPoller.cpp
*/
#include "engine_pch.h"
#include "include/platform/GLFW/GLFWInputPoller.h"
#include "core/application.h"
#include <GLFW\glfw3.h>

namespace Engine {

	bool GLFWInputPoller::isKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, keycode);
		return result == KEY_PRESS || result == KEY_REPEAT;
}

	bool GLFWInputPoller::isMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetMouseButton(window, button);
		return result == KEY_PRESS;
	}

}