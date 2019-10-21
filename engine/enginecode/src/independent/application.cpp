/** \file application.cpp
*/


#include "engine_pch.h"
#include "core/application.h"

#include <GLFW/glfw3.h>

//#ifdef NG_PLATFORM_WINDOWS
//#include "../platform/windows/GLFWWindowsSystem.h"
//#endif

//#ifdef NG_PLATFORM_WINDOWS
//m_windows = st::shared_ptr<Windows>(new GLFWWindowsSystem());
//#endif
//m_windows->start();
//ENG_CORE_INFO("Windows system initialised");

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

		m_Window = std::unique_ptr<Window>(Window::create());
	}

	bool Application::onClose(WindowCloseEvent & e)
	{
		ENG_CORE_INFO("Closing application.");
		m_running = false;	//solve m_running problem and don't forget about application.cpp and t2 in it
		return true;
	}
	
	bool Application::onResize(WindowResizeEvent & e)
	{
		ENG_CORE_INFO("Resize window to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event & e)	//Slide 34 Week2 to finish
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
		
		while (m_running)
		{
			glClearColor(0, 0, 1, 1);	//blue
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate(time);	//??? Does it make sense?

			start = std::chrono::high_resolution_clock::now();
			ENG_CLIENT_TRACE("Delta time: {0}", time/*(int)(1.0f/time)*/);
			end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> diff = end - start;
			time += diff.count();

			
			if (time > 3.0f)
			{
				WindowResizeEvent e(1024, 720);
				onEvent(e);
				m_running = false;
				//ENG_CORE_INFO("Time elapsed: {0}. Shutting down.", time);
			}
		}
		
		//float time = (float) glfwGetTime();	//!< Getting time
		//Timer timer = time - m_LastFrameTime;
		//m_LastFrameTime = time;
	}



}
