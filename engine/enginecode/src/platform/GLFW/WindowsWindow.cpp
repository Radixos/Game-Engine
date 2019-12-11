/** \file WindowsWindow.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "include/platform/GLFW/WindowsWindow.h"
#include "../platform/GLFW/GLFWWindowImpl.h"
#include "systems/Log.h"
#include "Event/EventSubclass.h"
#include "../platform/GLFW/GLFWCodes.h"
#include "Event/Event.h"

//#include <engine.h>

namespace Engine {

	static bool s_GLFWInitialized = false;

#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}
#endif // NG_PLATFORM_WINDOWS

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		close();
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		m_Data.m_title = props.m_title;
		m_Data.m_width = props.m_width;
		m_Data.m_height = props.m_height;

		ENG_CORE_INFO("Creating window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ENG_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.m_width, (int)props.m_height, m_Data.m_title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback([](GLenum source,
			GLenum type,
			GLenum id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParm)
		{
			ENG_CORE_INFO("OpenGL Debug [Type {0}] [Severity {1}]; {2}", type, severity, message);
		}, 0
		);

		//glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			callback(event);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			MouseMoved event(xPos, yPos);
			callback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case KEY_PRESS:
			{
				MouseButtonPressed event(button);
				callback(event);
				break;
			}
			case KEY_RELEASE:
			{	
				MouseButtonReleased event(button);
				callback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int unicodeCodePoint)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			KeyTyped event(unicodeCodePoint);
			callback(event);
			std::cout << (char)unicodeCodePoint;
		});

		/*glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int action, int repeatCount)
		{
			std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case KEY_PRESS:
			{
				KeyPressed event(keycode);
				callback(event);
				break;
			}
			case KEY_RELEASE:
			{
				KeyReleased event(keycode);
				callback(event);
				break;
			}
			}
		});*/

		//glfwSetScrollCallback(m_Window, [](GLFWwindow* window, float Xoffset, float Yoffset)
		//{

		//});
	}

	void WindowsWindow::close()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::onUpdate(float timestep)
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.m_isVSync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_Data.m_isVSync;
	}

	void WindowsWindow::onResize(unsigned int width, unsigned int height)
	{
		m_Data.m_width = width;
		m_Data.m_height = height;
	}



}