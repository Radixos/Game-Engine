/**
\file GLFWWindowsWindow.cpp
*/

#include "engine_pch.h"
#include "include/platform/GLFW/GLFWWindowsSystem.h"
//#include "../enginecode/include/platform/GLFW/GLFWWindowsSystem.h"

void Engine::GLFWWindowsSystem::start(SystemSignal init, ...)
{
	glfwInit();
}

void Engine::GLFWWindowsSystem::stop(SystemSignal close, ...)
{
	glfwTerminate();
}
