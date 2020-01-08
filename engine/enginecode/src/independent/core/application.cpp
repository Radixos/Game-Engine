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

#pragma region TempSetup
		//// Create a basic 3D
		//m_renderer.reset(Renderer::createBasic3D());
		//// Enable standard depth detest (Z-buffer)
		//m_renderer->actionCommand(RenderCommand::setDepthTestLessCommand(true));
		//// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		//m_renderer->actionCommand(RenderCommand::setBackfaceCullingCommand(true));

		//float FCvertices[6 * 24] = {
		//	-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
		//	 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
		//	 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
		//	-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
		//	-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
		//	 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
		//	 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
		//	-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
		//	-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
		//	 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
		//	 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
		//	-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
		//	-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
		//	 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
		//	 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
		//	-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
		//	-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
		//	-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
		//	-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
		//	-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
		//	0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
		//	0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
		//	0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
		//	0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		//};

		//float TPvertices[8 * 24] = {
		//	-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
		//	 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
		//	 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
		//	-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
		//	-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
		//	 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
		//	 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
		//	-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
		//	-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
		//	 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
		//	 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
		//	-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
		//	-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
		//	 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
		//	 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
		//	-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
		//	-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
		//	-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
		//	-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
		//	-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
		//	0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
		//	0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
		//	0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
		//	0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		//};

		//unsigned int indices[3 * 12] = {
		//	2, 1, 0,
		//	0, 3, 2,
		//	4, 5, 6,
		//	6, 7, 4,
		//	8, 9, 10,
		//	10, 11, 8,
		//	14, 13, 12,
		//	12, 15, 14,
		//	18, 17, 16,
		//	16, 19, 18,
		//	20, 21, 22,
		//	22, 23, 20
		//};

		//m_FCVertexBuffer.reset(VertexBuffer::create(FCvertices, sizeof(FCvertices), m_FClayout));
		//m_FCVAO->setVertexBuffer(m_FCVertexBuffer);

		//m_FCindexBuffer.reset(IndexBuffer::create(indices ,sizeof(indices)));
		//m_FCVAO->setindexBuffer(m_FCindexBuffer);

		//m_TPVertexBuffer.reset(VertexBuffer::create(TPvertices, sizeof(TPvertices), m_TPlayout));
		//m_TPVAO->setVertexBuffer(m_TPVertexBuffer);

		//m_TPindexBuffer.reset(IndexBuffer::create(indices, sizeof(indices)));
		//m_TPVAO->setindexBuffer(m_TPindexBuffer);

		//m_FCShader.reset(Shader::create("assets/shaders/flatColour.glsl"));
		//m_TPShader.reset(Shader::create("assets/shaders/texturedPhong.glsl"));

		//m_TPNumberTex.reset(Texture::createFromFile("assets/textures/letterCube.png"));
		//m_TPLetterTex.reset(Texture::createFromFile("assets/textures/numberCube.png"));

		//FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		//TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

		// End temporary code

#pragma endregion TempSetup

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
		
		while (m_running)
		{
			m_timer->setFrameStart();

			////m_renderer->actionCommand(RenderCommand::ClearDepthColourBufferCommand(0, 0, 1, 1));	//BLUE

			////glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			//glm::mat4 view = glm::lookAt(
			//	glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
			//	glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
			//	glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			//);

//			// Code to make the cube move.
//			glm::mat4 FCtranslation, TPtranslation;
//
//			if (m_goingUp)
//			{
//				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
//				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
//			}
//			else
//			{
//				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
//				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
//			}
//
//			if (m_timer->getTimeSinceMarkerStart() > 4.0f /*&& temp > 0*/)
//			{
//				m_timer->setMarkerStart();
//				m_goingUp = !m_goingUp;
//			}
//
//			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
//			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
//
//			// End of code to make the cube move.
//
//			glm::mat4 fcMVP = projection * view * FCmodel;
//
//			m_FCShader->bind();
//
//			m_FCVAO->bind();
//
//			GLuint loc;
//
//			m_FCShader->uploadData("u_MVP", &fcMVP[0][0]);
//
//			glDrawElements(GL_TRIANGLES, m_FCVAO->getDrawCount() , GL_UNSIGNED_INT, nullptr);
//
//			glm::mat4 tpMVP = projection * view * TPmodel;
//			m_TPShader->bind();
//			m_TPVAO->bind();
//
//			unsigned int m_texSlot;
//
//			if (m_goingUp) m_texSlot = m_TPLetterTex->getSlot();
//			else m_texSlot = m_TPNumberTex->getSlot();
//
//			m_TPShader->bind();
//			m_TPVAO->bind();
//
//			//glm::vec3 m_objectColour(0.2f, 0.8f, 0.5f);
//			glm::vec3 m_lightColour(1.0f, 1.0f, 1.0f);
//			glm::vec3 m_lightPosition(0.0f, 3.0f, -6.0f);
//			glm::vec3 m_viewPosition(0.0f, 0.0f, -4.5f);	//m_viewPosition = glm::vec3(0.0f, 0.0f, -4.5f);
//
//			m_TPShader->uploadData("u_MVP", &tpMVP[0][0]);
//			m_TPShader->uploadData("u_model", &TPmodel[0][0]);
//			//m_TPShader->uploadData("u_objectColour", &m_objectColour[0]);
//			m_TPShader->uploadData("u_lightColour", &m_lightColour[0]);
//			m_TPShader->uploadData("u_lightPos", &m_lightPosition[0]);
//			m_TPShader->uploadData("u_viewPos", &m_viewPosition[0]);
//			m_TPShader->uploadData("u_texData", (void*)m_texSlot);
//
//			glDrawElements(GL_TRIANGLES, m_TPVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
//
//			// End temporary code
//#pragma endregion TempDrawCode
//
//			m_windows->onUpdate(s_timestep);
//
//			//if (time > 3.0f)
//			//{
//			//	WindowResizeEvent e(1024, 720);
//			//	onEvent(e);
//			//	m_running = false;
//			//	//ENG_CORE_INFO("Time elapsed: {0}. Shutting down.", time);
//			//}
//			//end = std::chrono::high_resolution_clock::now();
//			//std::chrono::duration<float> diff = end - start;
//			//s_timestep = diff.count();

			s_timestep = m_timer->getTimeSinceFrameStart();
			//ENG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));
		
#ifdef NG_DEBUG
			ENG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));
#endif
			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
				(*it)->onUpdate(s_timestep);

			m_window->onUpdate(s_timestep);
		
		}
	}
}