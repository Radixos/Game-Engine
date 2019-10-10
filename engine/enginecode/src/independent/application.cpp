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
		//!Starting systems
		m_logger.reset(new Log);
		m_logger->start();
		ENG_CORE_INFO("Logger started");
		//m_timer->start();	//fix the cpp
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		float time = (float) glfwGetTime();	//!< Getting time
		Timer timer = time - m_LastFrameTime;
		m_LastFrameTime = time;
	}

}
