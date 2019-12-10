/** \file Timer.h
*/
#pragma once

#include "systems/system.h"
#include <chrono>

namespace Engine {

	//class Timer : public System
	//{
	//private:
	//	float m_Time;
	//public:
	//	Timer(float time = 0.0f)
	//		: m_Time(time) {}
	//	float GetSeconds() const { return m_Time; }
	//	float GetMilliSeconds() const { return m_Time * 1000.0f; }
	//
	//	virtual void start(SystemSignal init = SystemSignal::None, ...) override;
	//	virtual void stop(SystemSignal close = SystemSignal::None, ...) override;
	//};

	class Timer : public System
	{
	public:
		Timer(float time = 0.0f) : m_time(time) {}
		float GetSeconds() const { return 1E9; }
		float GetMilliSeconds() const { return 1E6; }
		void start(SystemSignal init = SystemSignal::None, ...) override
		{
			setFrameStart();
			setAppStart();
			setMarkerStart();
		}
		void stop(SystemSignal close = SystemSignal::None, ...) override {}

		void setFrameStart() { m_frameStart = std::chrono::high_resolution_clock::now(); }
		float getTimeSinceFrameStart() { return (std::chrono::high_resolution_clock::now() - m_frameStart).count() / GetSeconds(); }
		float getTimeSinceFrameStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_frameStart).count() / GetMilliSeconds();}

		void setAppStart() { m_appStart = std::chrono::high_resolution_clock::now(); }
		float getTimeSinceAppStart() { return (std::chrono::high_resolution_clock::now() - m_appStart).count() / GetSeconds(); }
		float getTimeSinceAppStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_appStart).count() / GetMilliSeconds(); }

		void setMarkerStart() { m_markerStart = std::chrono::high_resolution_clock::now(); }
		float getTimeSinceMarkerStart() { return (std::chrono::high_resolution_clock::now() - m_markerStart).count() / GetSeconds(); }
		float getTimeSinceMarkerStartAsMilliseconds() { return (std::chrono::high_resolution_clock::now() - m_markerStart).count() / GetMilliSeconds(); }
	private:
		float m_time;
		std::chrono::high_resolution_clock::time_point m_appStart;
		std::chrono::high_resolution_clock::time_point m_frameStart;
		std::chrono::high_resolution_clock::time_point m_markerStart;
	};
}