/**
\file GLFWInputPoller.cpp
*/
#include "engine_pch.h"
#include "include/platform/GLFW/GLFWInputPoller.h"
#include <GLFW\glfw3.h>
#include "include/platform/GLFW/GLFWCodes.h"
#include "core/application.h"

namespace Engine {

	bool GLFWInputPoller::isKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetKey(window, keycode);
		return result == KEY_PRESS || result == KEY_REPEAT;
	}

	bool GLFWInputPoller::isMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		int result = glfwGetMouseButton(window, button);
		return result == KEY_PRESS;
	}

	glm::vec2 GLFWInputPoller::getMousePositionImpl()
	{
		double xPos, yPos;
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		glfwGetCursorPos(window, &xPos, &yPos);
		return glm::vec2(xPos, yPos);
	}

	float GLFWInputPoller::getMouseXImpl()
	{
		double xPos, yPos;
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		glfwGetCursorPos(window, &xPos, &yPos);
		return xPos;
	}

	float GLFWInputPoller::getMouseYImpl()
	{
		double xPos, yPos;
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindow()->getNativeWindow());
		glfwGetCursorPos(window, &xPos, &yPos);
		return yPos;
	}
	
}