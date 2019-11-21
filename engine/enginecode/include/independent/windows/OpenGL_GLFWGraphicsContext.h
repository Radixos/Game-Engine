#pragma once
/** \class Implementation to a graphics context for openGL and GLFW */

#include "graphicsContext.h"
#include "include/platform/GLFW/GLFWWindowImpl.h"

//namespace Engine {
	class OpenGL_GLFWGraphicsContext : GraphicsContext
	{
	public:
		OpenGL_GLFWGraphicsContext(GLFWwindow window);
		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
//}