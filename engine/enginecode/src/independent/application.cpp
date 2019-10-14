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

	void Application::onEvent(Event & e)
	{
		if (e.getEventType() == EventType::WindowResize)
		{
			//Cast the event
			WindowResizeEvent resize = (WindowResizeEvent&)e;
			ENG_CORE_INFO("Window resize event. Width {0}. Height {1}", resize.getWidth(), resize.getHeight());
		}
	}

	void Application::run()
	{
		//For fps see week 2
		//delta = 1.0-timestep;
		//timestep/delta;

		std::chrono::high_resolution_clock::time_point start, end;
		start = std::chrono::high_resolution_clock::now();
		float time = 0.f;

		while (true)
		{
			start = std::chrono::high_resolution_clock::now();
			ENG_CLIENT_TRACE("Delta time: {0}", time);
			end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> diff = end - start;
			time += diff.count();
		}

		//float time = (float) glfwGetTime();	//!< Getting time
		//Timer timer = time - m_LastFrameTime;
		//m_LastFrameTime = time;
	}



}
