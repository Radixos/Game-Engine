#include "engine_pch.h"
#include "WindowsWindow.h"

namespace Engine {

	static bool s_GLFWInitialized = false;

	Window* Window::create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		m_Data.Title = props.m_title;
		m_Data.Width = props.m_width;
		m_Data.Height = props.m_height;

		ENG_CORE_INFO("Creating window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ENG_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.m_width, (int)props.m_height, (int)m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}