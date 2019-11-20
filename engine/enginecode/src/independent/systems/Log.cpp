/** \file Log.cpp
*/

#include "engine_pch.h"
#include "systems/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger = spdlog::stderr_color_mt("Client");
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger = spdlog::stderr_color_mt("Engine");

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");	//!< Pattern for Logger display
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");	//!< Pattern for Logger display
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::start(SystemSignal init, ...)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");	//!< Pattern for Logger display
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::stop(SystemSignal close, ...)
	{

	}

}