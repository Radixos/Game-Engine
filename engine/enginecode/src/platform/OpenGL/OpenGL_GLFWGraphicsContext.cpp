/** \file OpenGL_GLFWGraphicsContext.cpp
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGL_GLFWGraphicsContext.h"
#include <include\independent\systems\Log.h>

//#include <glad/glad.h>

//OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow* window) : m_window(window)
//{
//	ENG_CORE_INFO("Window handle null");
//}
//
//void OpenGL_GLFWGraphicsContext::init()
//{
//	glfwMakeContextCurrent(m_window);
//	int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//	
//	ENG_CORE_INFO("OpenGL info:");
//	ENG_CORE_INFO("\n	Vendor info: {0}\n	Renderer info:{1}\n	Version info:{2}",glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
//
//	glEnable(GL_DEBUG_OUTPUT);
//	glDebugMessageCallback([](GLenum source,
//		GLenum type,
//		GLenum id,
//		GLenum severity,
//		GLsizei length,
//		const GLchar* message,
//		const void* userParm)
//	{
//		ENG_CORE_INFO("OpenGL Debug [Type {0}] [Severity {1}]; {2}", type, severity, message);
//	}, 0
//	);
//}
//
//void OpenGL_GLFWGraphicsContext::swapBuffers()
//{
//	glfwSwapBuffers(m_window);
//}