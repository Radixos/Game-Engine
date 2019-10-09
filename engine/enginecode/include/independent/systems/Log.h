#pragma once

//#include "system.h"
#include "spdlog/spdlog.h"

namespace Engine {

	class Log
	{
	public:
		static void Init();	//!< Initializing constructor

		inline static std::shared_ptr<spdlog::logger>&GetCoreLogger() { return s_CoreLogger; }	//!< inline static pointer for Core Logger
		inline static std::shared_ptr<spdlog::logger>&GetClientLogger() { return s_ClientLogger; }	//!< inline static pointer for Client Logger

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// HOW MACROS WORK?

//!Core log macros

#define ENG_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENG_CORE_WARN(...)  ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENG_CORE_INFO(...)  ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENG_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENG_CORE_FATAL(...) ::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__) 

//!Client log macros

#define ENG_CLIENT_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENG_CLIENT_WARN(...)  ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENG_CLIENT_INFO(...)  ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENG_CLIENT_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENG_CLIENT_FATAL(...) ::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__) 