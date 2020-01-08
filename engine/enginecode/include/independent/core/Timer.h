/** \class Timer class
*/
#pragma once

#include "systems/system.h"
#include <chrono>

namespace Engine {

	class Timer : public System
	{
	public:
		Timer(float time = 0.0f) : m_time(time) {}	//!<Timer constructor
		float GetSeconds() const { return 1E9; }	//!<GetSeconds function
		float GetMilliSeconds() const { return 1E6; }	//!<GetMiliSeconds function
		void start(SystemSignal init = SystemSignal::None, ...) override	//!<Start functrion for time
		{
			setFrameStart();
			setAppStart();
			setMarkerStart();
		}
		void stop(SystemSignal close = SystemSignal::None, ...) override {}	//!<Stop function for time

		std::chrono::high_resolution_clock::time_point setFrameStart() { return m_frameStart = std::chrono::high_resolution_clock::now(); }	//!<Frame start function
		float getTimeSinceFrameStart() { return (std::chrono::high_resolution_clock::now() - m_frameStart).count() / GetSeconds(); }	//!<getTimeSinceFrameStart function as seconds
		float getTimeSinceFrameStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_frameStart).count() / GetMilliSeconds();}	//!<getTimeSinceFrameStart function as miliseconds

		void setAppStart() { m_appStart = std::chrono::high_resolution_clock::now(); }	//!<App start function
		float getTimeSinceAppStart() { return (std::chrono::high_resolution_clock::now() - m_appStart).count() / GetSeconds(); }	//!<getTimeSinceAppStart function as seconds
		float getTimeSinceAppStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_appStart).count() / GetMilliSeconds(); }	//!<getTimeSinceAppStart function as miliseconds

		void setMarkerStart() { m_markerStart = std::chrono::high_resolution_clock::now(); }	//!<Marker start function
		float getTimeSinceMarkerStart() { return (std::chrono::high_resolution_clock::now() - m_markerStart).count() / GetSeconds(); }	//!<getTimeSinceMarkerStart function as seconds
		float getTimeSinceMarkerStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_markerStart).count() / GetMilliSeconds(); }	//!<getTimeSinceMarkerStart function as miliseconds
	private:
		float m_time;	//!<Time variable
		std::chrono::high_resolution_clock::time_point m_frameStart;	//!<Frame start time point
		std::chrono::high_resolution_clock::time_point m_appStart;	//!<App start time point
		std::chrono::high_resolution_clock::time_point m_markerStart;	//!<Marker start time point
	};
}