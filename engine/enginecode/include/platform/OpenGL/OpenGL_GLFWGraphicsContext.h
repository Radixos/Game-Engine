/** \class implementation to a graphics context for openGL and GLFW
*/
#pragma once

#include "windows/graphicsContext.h"
#include "include/platform/GLFW/GLFWWindowImpl.h"

class OpenGL_GLFWGraphicsContext : public GraphicsContext
{
public:
	OpenGL_GLFWGraphicsContext(GLFWwindow* window);
	void init() override;
	void swapBuffers() override;
private:
	GLFWwindow* m_window;
};