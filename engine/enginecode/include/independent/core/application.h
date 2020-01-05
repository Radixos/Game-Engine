/** \file application.h
*/
#pragma once

#include "core/Timer.h"
#include "systems/Log.h"
//#include "Event/Event.h"
#include "Event/EventSubclass.h"
#include "windows/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef NG_PLATFORM_WINDOWS
#include "../platform/GLFW/GLFWWindowsSystem.h"
#endif // NG_PLATFORM_WINDOWS
#include <include\independent\Rendering\Buffer.h>
#include <include\independent\Rendering\VertexArray.h>
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Rendering/Renderer.h"
#include <include\independent\Layer\LayerStack.h>

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<LayerStack> m_layerStack;
	private:
		std::shared_ptr<Log> m_logger;
		std::shared_ptr<Timer> m_timer;
		std::shared_ptr<Window> m_windows;
		std::shared_ptr<GLFWWindowsSystem> m_system;
		std::shared_ptr<VertexArray> m_FCVAO;
		std::shared_ptr<VertexArray> m_TPVAO;
		std::shared_ptr<VertexBuffer> m_FCVertexBuffer;
		std::shared_ptr<VertexBuffer> m_TPVertexBuffer;
		std::shared_ptr<IndexBuffer> m_FCindexBuffer;
		std::shared_ptr<IndexBuffer> m_TPindexBuffer;
		std::shared_ptr<Texture> m_TPNumberTex;
		std::shared_ptr<Texture> m_TPLetterTex;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<Shader> m_FCShader;
		std::shared_ptr<Shader> m_TPShader;

		BufferLayout m_TPlayout = 
		{
			{ShaderDataType::Float3},
			{ShaderDataType::Float3},
			{ShaderDataType::Float2},
		};
		BufferLayout m_FClayout = 
		{
			{ShaderDataType::Float3},
			{ShaderDataType::Float3},
		};

		static Application* s_instance; //!< Singleton instance of the application
		float m_LastFrameTime = 0.0f;
		bool m_running = true;

		bool onClose(WindowCloseEvent& e);	//!<On close event
		bool onResize(WindowResizeEvent& e);	//!<On resize event
		bool onLostFocus(WindowLostFocus& e);	//!<On lost focus event
		bool onMouseMoved(MouseMoved& e);	//!<On mouse moved event
		bool onMouseButtonPressed(MouseButtonPressed& e);	//!<On mouse button pressed
		bool onMouseButtonReleased(MouseButtonReleased& e);	//!<On mouse button released
		//bool onMouseScrolled(MouseScrolled& e);	//!<On mouse scrolled
		bool onKeyPressed(KeyPressed& e);	//!<On key pressed
		bool onKeyReleased(KeyReleased& e);	//!<On key released
		bool onKeyTyped(KeyTyped& e);	//!<On key Typed

		int temp = 0;

		static float s_timestep; //!< last frame timestep
		static glm::ivec2 s_screenResolution; //!< Screen res

#pragma region TempVars
// Temp stuff
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 0.f; // How much timer has elasped?
#pragma endregion TempVars

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; }	//!< Instance getter from singleton pattern
		inline static float getTimestep() { return s_timestep; }	//!<Declaring and defining function for returning the timestep
		inline std::shared_ptr<Window> getWindow() { return m_windows; }	//!<Declaring and defining function for returning the window
		void onEvent(Event& e);	//!< Called when an event happens
		//bool onClose(WindowCloseEvent& e); //!< On close event
		//bool onResize(WindowResizeEvent& e); //!< On resize event
		//bool onKeyPressed(KeyPressedEvent& e); //!< On keypress event
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}