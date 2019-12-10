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
	private:
		std::shared_ptr<Log> m_logger;
		std::shared_ptr<Timer> m_timer;
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<GLFWWindowsSystem> m_system;


		static Application* s_instance; //!< Singleton instance of the application
		//Timer m_timer; //!< Timer for measuring time
		float m_LastFrameTime = 0.0f;
		bool m_running = true;

		bool onClose(WindowCloseEvent& e);	//!< On close event
		bool onResize(WindowResizeEvent& e);	//!< On resize event

		static float s_timestep; //!< last frame timestep
		static glm::ivec2 s_screenResolution; //!< Screen res

#pragma region TempVars
// Temp stuff
		unsigned int m_FCvertexArray; // Flat Colour VAO
		unsigned int m_FCvertexBuffer;// Flat Colour VBO
		unsigned int m_TPvertexArray; // Textured Phong VAO
		unsigned int m_TPvertexBuffer;// Textured Phong VBO
		unsigned int m_FCindexBuffer; // Index buffer for colour cube
		unsigned int m_TPindexBuffer; // Index buffer for texture Phong cube
		unsigned int m_FCprogram; // Flat colour shader ID
		unsigned int m_TPprogram; // Textured Phong shader ID
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 0.f; // How much timer has elasped?
#pragma endregion TempVars

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline static float getTimestep() { return s_timestep; }
		inline std::shared_ptr<Window> getWindow() { return m_Window; }
		void onEvent(Event& e);	//!< Called when an event happens
		//bool onClose(WindowCloseEvent& e); //!< On close event
		//bool onResize(WindowResizeEvent& e); //!< On resize event
		//bool onKeyPressed(KeyPressedEvent& e); //!< On keypress event
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}