/** \file OpenGL_GLFWGraphicsContext.cpp
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_GLFWGraphicsContext.h"
#include <include\independent\systems\Log.h>

//OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow* window) : m_window(window)
//{
//
//}
//
//void OpenGL_GLFWGraphicsContext::init()
//{
//	glfwMakeContextCurrent(m_window);
//	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//	ENG_CORE_INFO(result, "Failed to initialise GLAD");
//}
//
//void OpenGL_GLFWGraphicsContext::swapBuffers()
//{
//	glfwSwapBuffers(m_window);
//}