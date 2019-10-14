/** \file application.h
*/
#pragma once

#include "core/Timer.h"
#include "systems/Log.h"
#include "Event/Event.h"

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
		std::shared_ptr<Log> m_logger;
		std::shared_ptr<Timer> m_timer;
	private:
		static Application* s_instance; //!< Singleton instance of the application
		//Timer m_timer; //!< Timer for measuring time
		float m_LastFrameTime = 0.0f;
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void onEvent(Event& e);
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}