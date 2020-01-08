/**
\file application.cpp
*/

/*
TO DO:
Layer Stack
Draw 2D text
Cameras
JSON Loader
Testing
dOxygen
Report
ubo
*/

//renderer, camera, layer, clean app

#include "engine_pch.h"

#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
//#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

#pragma endregion TempIncludes

#include "core/application.h"
#include "Event/EventSubclass.h"
#include "Event/EventDispatcher.h"
#include <include\platform\OpenGL\OpenGLShader.h>
#include <include\platform\OpenGL\OpenGLTexture.h>

//#ifdef NG_PLATFORM_WINDOWS
//#include "../platform/GLFW/GLFWWindowsSystem.h"
//#endif

//#ifdef NG_PLATFORM_WINDOWS
//m_windows = st::shared_ptr<Windows>(new GLFWWindowsSystem());
//#endif
//m_windows->start();
//ENG_CORE_INFO("Windows system initialised");

#ifdef NG_PLATFORM_WINDOWS
#include "include/platform/GLFW/WindowsWindow.h"
//#include "include/platform/GLFW/InputPoller.h"
#include "../platform/GLFW/GLFWWindowsSystem.h"
#endif // NG_PLATFORM_WINDOWS
#include <include\independent\Rendering\RenderCommand.h>

namespace Engine {
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 0.f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);

#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		//!Starting systems
		m_logger.reset(new Log);	//() - same in rest
		m_logger->start();
		ENG_CORE_INFO("Logger started");
		m_timer.reset(new Timer);
		m_timer->start();
		ENG_CORE_INFO("Timer initialised");
		//m_system.reset(new GLFWWindowsSystem);
		//m_system->start();
		//ENG_CORE_INFO("GLFWWindowsSystem initialised");

#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem = std::shared_ptr<WindowSystem>(new GLFWWindowsSystem);
#endif // NG_PLATFORM_WINDOWS

		m_window.reset(Window::create());
		ENG_CORE_INFO("GLFWWindowsSystem initialised");

		//m_windows->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		//ENG_CLIENT_INFO("Windows system initialised");
		
		m_layerStack.reset(new LayerStack());
		m_layerStack->begin();	//???
		ENG_CORE_INFO("LayerStack initialised");
		
		// Create window
		//m_windows = std::shared_ptr<Window>(Window::create());
		m_window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		// Set screen resolution
		Application::s_screenResolution = glm::ivec2(m_window->getWidth(), m_window->getHeight());

		//m_FCVAO.reset(VertexArray::create());
		//m_TPVAO.reset(VertexArray::create());

		//Reset timer
		m_timer->getTimeSinceFrameStart();	//???

		// Reset timer
		m_timer->GetSeconds();
	}

	Application::~Application()
	{
		// Stop systems
		m_timer->stop();
		m_logger->stop();
	}

	void Application::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMoved>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
	
		for (auto it = m_layerStack->end(); it != m_layerStack->begin(); )
		{
			(*--it)->onEvent(e);
			if (e.handled(true)) break;
		}
	}

	bool Application::onClose(WindowCloseEvent& e)
	{
		ENG_CORE_INFO("Closing application.");
		m_running = false;
		return true;
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		ENG_CORE_INFO("Resize window to {0}x{1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onLostFocus(WindowLostFocus& e)
	{
		ENG_CORE_INFO("Window lost focus on Pos X: {0} / Pos Y: {1}", e.getposX(), e.getposY());
		return true;
	}

	bool Application::onMouseMoved(MouseMoved& e)
	{
		ENG_CORE_INFO("Mouse current Pos X: {0} | {1}", e.getoffsetX(), e.getoffsetY());
		return true;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressed& e)
	{
		if (e.getButton() == GLFW_MOUSE_BUTTON_LEFT) std::cout << "Left Mouse Button pressed" << std::endl;
		if (e.getButton() == GLFW_MOUSE_BUTTON_MIDDLE) std::cout << "Middle Mouse Button pressed" << std::endl;
		if (e.getButton() == GLFW_MOUSE_BUTTON_RIGHT) std::cout << "Right Mouse Button pressed" << std::endl;
		return true;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleased& e)
	{
		if (e.getButton() == GLFW_MOUSE_BUTTON_LEFT) std::cout << "Left Mouse Button released" << std::endl;
		if (e.getButton() == GLFW_MOUSE_BUTTON_MIDDLE) std::cout << "Middle Mouse Button released" << std::endl;
		if (e.getButton() == GLFW_MOUSE_BUTTON_RIGHT) std::cout << "Right Mouse Button released" << std::endl;
		return true;
	}

	//bool Application::onMouseScrolled(MouseScrolled& e)
	//{
	//	if(e.get == GLFW)
	//}

	bool Application::onKeyPressed(KeyPressed& e)
	{
		//ENG_CORE_ASSERT("Key {0} pressed.", e.getKeycode);
		return true;
	}

	bool Application::onKeyReleased(KeyReleased& e)
	{
		//ENG_CORE_ASSERT("Key {0} released.", e.getKeycode());
		return true;
	}

	bool Application::onKeyTyped(KeyTyped& e)
	{
		ENG_CORE_INFO("Key {0} typed", e.getKeycode());	//Why the text doesn't show up? (Check WindowsWindow.cpp)
		return true;
	}

	//bool Application::onKeyPressed(KeyPressedEvent & e)
	//{
	//	if (e.GetKeyCode() == KEY_ESCAPE) //Escape
	//	{
	//		m_running = false;
	//		m_window->close();
	//		return true;
	//	}
	//	return false;
	//}

	void Application::run()
	{
		s_timestep = 0;
		
		std::chrono::high_resolution_clock::time_point fS, fE;
		std::chrono::duration<float> ts;

		while (m_running)
		{
			fS = m_timer->setFrameStart();
			
			//s_timestep = m_timer->getTimeSinceFrameStart();
			//ENG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));
		
#ifdef NG_DEBUG
			//ENG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));
#endif
			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
			{
				
				(*it)->onUpdate(s_timestep);
			}
		
			m_window->onUpdate(s_timestep);

			fE = m_timer->setFrameStart();

			ts = fE - fS;
			s_timestep = ts.count();

			ENG_CORE_ERROR("{0}", s_timestep);
		}
	}
}