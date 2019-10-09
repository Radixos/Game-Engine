/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"

#include <GLFW/glfw3.h>

namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
	}

	Application::~Application()
	{
	}

	

	void Application::run()
	{
		float time = (float) glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}

}
