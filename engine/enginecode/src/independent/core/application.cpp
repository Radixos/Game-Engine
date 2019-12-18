/** \file application.cpp
*/

/*
TO DO:
Composable Game Objects
Layer Stack
Draw 2D text
Cameras
JSON Loader
Testing
dOxygen
Report
*/

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
#endif // NG_PLATFORM_WINDOWS

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
		m_logger.reset(new Log);
		m_logger->start();
		ENG_CORE_INFO("Logger started");
		m_timer.reset(new Timer);
		m_timer->start();
		ENG_CORE_INFO("Timer initialised");

		m_system.reset(new GLFWWindowsSystem);
		m_system->start();
		//m_Window = std::shared_ptr<Window>(Window::create());
#ifdef NG_PLATFORM_WINDOWS
		m_Window.reset(Window::create());
#endif // NG_PLATFORM_WINDOWS
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		//m_Window->start();
		ENG_CLIENT_INFO("Windows system initialised");
		// Create window
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		// Set screen resolution
		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

		m_FCVAO.reset(VertexArray::create());
		m_TPVAO.reset(VertexArray::create());

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		m_FCVertexBuffer.reset(VertexBuffer::create(FCvertices, sizeof(FCvertices), m_FClayout));
		m_FCVAO->setVertexBuffer(m_FCVertexBuffer);

		m_FCindexBuffer.reset(IndexBuffer::create(indices ,sizeof(indices)));
		m_FCVAO->setindexBuffer(m_FCindexBuffer);

		//m_FCShader = m_resources->

		std::string FCvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexColour;
				out vec3 fragmentColour;
				uniform mat4 u_MVP;
				void main()
				{
					fragmentColour = a_vertexColour;
					gl_Position =  u_MVP * vec4(a_vertexPosition,1);
				}
			)";

		std::string FCFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 fragmentColour;
				void main()
				{
					colour = vec4(fragmentColour, 1.0);
				}
		)";

		GLuint FCVertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = FCvertSrc.c_str();
		glShaderSource(FCVertShader, 1, &source, 0);
		glCompileShader(FCVertShader);

		GLint isCompiled = 0;
		glGetShaderiv(FCVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCVertShader, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCVertShader);
			return;
		}

		GLuint FCFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = FCFragSrc.c_str();
		glShaderSource(FCFragShader, 1, &source, 0);
		glCompileShader(FCFragShader);

		glGetShaderiv(FCFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCFragShader, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCFragShader);
			glDeleteShader(FCVertShader);

			return;
		}

		m_FCprogram = glCreateProgram();
		glAttachShader(m_FCprogram, FCVertShader);
		glAttachShader(m_FCprogram, FCFragShader);
		glLinkProgram(m_FCprogram);

		GLint isLinked = 0;
		glGetProgramiv(m_FCprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_FCprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_FCprogram, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_FCprogram);
			glDeleteShader(FCVertShader);
			glDeleteShader(FCFragShader);

			return;
		}

		glDetachShader(m_FCprogram, FCVertShader);
		glDetachShader(m_FCprogram, FCFragShader);

		// Added textuer phong shader and cube

		m_TPVertexBuffer.reset(VertexBuffer::create(TPvertices, sizeof(TPvertices), m_TPlayout));
		m_TPVAO->setVertexBuffer(m_TPVertexBuffer);

		m_TPindexBuffer.reset(IndexBuffer::create(indices, sizeof(indices)));
		m_TPVAO->setindexBuffer(m_TPindexBuffer);

		std::string TPvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexNormal;
				layout(location = 2) in vec2 a_texCoord;
				out vec3 fragmentPos;
				out vec3 normal;
				out vec2 texCoord;
				uniform mat4 u_model;
				uniform mat4 u_MVP;
				void main()
				{
					fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
					normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
					texCoord = vec2(a_texCoord.x, a_texCoord.y);
					gl_Position =  u_MVP * vec4(a_vertexPosition,1.0);
				}
			)";

		std::string TPFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 normal;
				in vec3 fragmentPos;
				in vec2 texCoord;
				uniform vec3 u_lightPos; 
				uniform vec3 u_viewPos; 
				uniform vec3 u_lightColour;
				uniform sampler2D u_texData;
				void main()
				{
					float ambientStrength = 0.4;
					vec3 ambient = ambientStrength * u_lightColour;
					vec3 norm = normalize(normal);
					vec3 lightDir = normalize(u_lightPos - fragmentPos);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * u_lightColour;
					float specularStrength = 0.8;
					vec3 viewDir = normalize(u_viewPos - fragmentPos);
					vec3 reflectDir = reflect(-lightDir, norm);  
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
					vec3 specular = specularStrength * spec * u_lightColour;  
					
					colour = vec4((ambient + diffuse + specular), 1.0) * texture(u_texData, texCoord);
				}
		)";

		GLuint TPVertShader = glCreateShader(GL_VERTEX_SHADER);

		source = TPvertSrc.c_str();
		glShaderSource(TPVertShader, 1, &source, 0);
		glCompileShader(TPVertShader);

		isCompiled = 0;
		glGetShaderiv(TPVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPVertShader, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPVertShader);
			return;
		}

		GLuint TPFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = TPFragSrc.c_str();
		glShaderSource(TPFragShader, 1, &source, 0);
		glCompileShader(TPFragShader);

		glGetShaderiv(TPFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPFragShader, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPFragShader);
			glDeleteShader(TPVertShader);

			return;
		}

		m_TPprogram = glCreateProgram();
		glAttachShader(m_TPprogram, TPVertShader);
		glAttachShader(m_TPprogram, TPFragShader);
		glLinkProgram(m_TPprogram);

		isLinked = 0;
		glGetProgramiv(m_TPprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_TPprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_TPprogram, maxLength, &maxLength, &infoLog[0]);
			ENG_CORE_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_TPprogram);
			glDeleteShader(TPVertShader);
			glDeleteShader(TPFragShader);

			return;
		}

		glDetachShader(m_TPprogram, FCVertShader);
		glDetachShader(m_TPprogram, FCFragShader);

		m_TPNumberTex.reset(Texture::createFromFile("assets/textures/letterCube.png"));
		m_TPLetterTex.reset(Texture::createFromFile("assets/textures/numberCube.png"));

		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

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

	void Application::onEvent(Event & e)	//Slide 34 Week2 to finish
	{
		//if (e.getEventType() == EventType::WindowResize)
				//{
				//	//Cast the event
				//	WindowResizeEvent resize = (WindowResizeEvent&)e;
				//	ENG_CORE_INFO("Window resize event. Width {0}. Height {1}", resize.getWidth(), resize.getHeight());
				//
				//	EventDispatcher dispatcher(e);
				//	dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
				//	dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
				//}

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowLostFocus>(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMoved>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleased>(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
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
		////For fps see week 2
		////delta = 1.0-timestep;
		////timestep/delta;

		//std::chrono::high_resolution_clock::time_point start, end;
		////start = std::chrono::high_resolution_clock::now();
		//float time = 0.f;

		s_timestep = 0;
		//ENG_CLIENT_INFO("FPS: {0}", (int)(1.0f / s_timestep));
		
		while (m_running)
		{
			m_timer->setFrameStart();

			//start = std::chrono::high_resolution_clock::now();

			glClearColor(0, 0, 1, 1);	//blue
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
			}
			else
			{
				FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
			}

			//if (m_timer->getTimeSinceMarkerStart() == 2.0f && temp == 0)
			//{
			//	m_timer->setMarkerStart();
			//	m_goingUp = !m_goingUp;
			//	temp++;
			//}

			if (m_timer->getTimeSinceMarkerStart() > 4.0f /*&& temp > 0*/)
			{
				m_timer->setMarkerStart();
				m_goingUp = !m_goingUp;
			}

			//m_Window->onUpdate(time);	//??? Does it make sense?
			//ENG_CLIENT_TRACE("Delta time: {0}", time/*(int)(1.0f/time)*/);
			//end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<float> diff = end - start;
			//time += diff.count();

			//m_timeSummed += s_timestep;
			//if (m_timeSummed > 20.0f) {
			//	m_timeSummed = 0.f;
			//	m_goingUp = !m_goingUp;
			//}

			//if (time > 3.0f)
			//{
			//	WindowResizeEvent e(1024, 720);
			//	onEvent(e);
			//	m_running = false;
			//	//ENG_CORE_INFO("Time elapsed: {0}. Shutting down.", time);
			//}

			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;
			glUseProgram(m_FCprogram);
			//glBindVertexArray(m_FCvertexArray);

			//m_FCShader->bind();
			m_FCVAO->bind();

			GLuint loc;

			//loc = glGetUniformLocation(m_FCShader->id(), "u_MVP");
			//glUniformMatrix4fv(loc, 1, GL_FALSE, &fcMVP[0][0]);

			GLuint MVPLoc = glGetUniformLocation(m_FCprogram, "u_MVP");
			glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, &fcMVP[0][0]);
			glDrawElements(GL_TRIANGLES, m_FCVAO->getDrawCount() , GL_UNSIGNED_INT, nullptr);

			glm::mat4 tpMVP = projection * view * TPmodel;
			m_TPShader.reset(new OpenGLShader);	//TO FINISH
			m_TPShader->bind();
			m_TPVAO->bind();

			m_TPShader->uploadMat4("u_MVP", &tpMVP[0][0]);
			m_TPShader->uploadMat4("u_model", &tpMVP[0][0]);

			glm::vec3 m_lightPosition (0.0f, 3.0f, -6.0f);
			glm::vec3 m_viewPosition (0.0f, 0.0f, -4.5f);	//m_viewPosition = glm::vec3(0.0f, 0.0f, -4.5f);
			glm::vec3 m_lightColour (1.0f, 1.0f, 1.0f);

			m_TPShader->uploadFloat3("u_lightPos", &m_lightPosition[0]);
			m_TPShader->uploadFloat3("u_viewPos", &m_viewPosition[0]);
			m_TPShader->uploadFloat3("u_lightColour", &m_lightColour[0]);

			unsigned int m_texSlot;

			if (m_goingUp) m_texSlot = m_TPLetterTex->getSlot();
			else m_texSlot = m_TPNumberTex->getSlot();

			m_TPShader->uploadInt("u_texData", m_texSlot);

			glUseProgram(m_TPprogram);
			//glBindVertexArray(m_TPvertexArray);
			m_TPVAO->bind();
			loc = glGetUniformLocation(m_TPprogram, "u_MVP");
			glUniformMatrix4fv(loc, 1, GL_FALSE, &tpMVP[0][0]);
			
			GLuint modelLoc = glGetUniformLocation(m_TPprogram, "u_model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &TPmodel[0][0]);

			//m_FCShader->uploadMat4("u_MVP", &fcMVP[0][0]);

			GLuint colLoc = glGetUniformLocation(m_TPprogram, "u_objectColour");
			glUniform3f(colLoc, 0.2f, 0.8f, 0.5f);

			GLuint lightColLoc = glGetUniformLocation(m_TPprogram, "u_lightColour");
			glUniform3f(lightColLoc, 1.0f, 1.0f, 1.0f);

			GLuint lightPosLoc = glGetUniformLocation(m_TPprogram, "u_lightPos");
			glUniform3f(lightPosLoc, 1.0f, 4.0f, -6.0f);

			GLuint viewPosLoc = glGetUniformLocation(m_TPprogram, "u_viewPos");
			glUniform3f(viewPosLoc, 0.0f, 0.0f, -4.5f);

			GLuint texDataLoc = glGetUniformLocation(m_TPprogram, "u_texData");
			glUniform1i(texDataLoc, m_texSlot);

			glDrawElements(GL_TRIANGLES, m_TPVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			// End temporary code
#pragma endregion TempDrawCode

			m_Window->onUpdate(s_timestep);

			//if (time > 3.0f)
			//{
			//	WindowResizeEvent e(1024, 720);
			//	onEvent(e);
			//	m_running = false;
			//	//ENG_CORE_INFO("Time elapsed: {0}. Shutting down.", time);
			//}
			//end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<float> diff = end - start;
			//s_timestep = diff.count();
			s_timestep = m_timer->getTimeSinceFrameStart();
			//ENG_CORE_INFO("FPS: {0}", (int)(1.0f / s_timestep));
		}
		
		//float time = (float) glfwGetTime();	//!< Getting time
		//Timer timer = time - m_LastFrameTime;
		//m_LastFrameTime = time;
	}
}