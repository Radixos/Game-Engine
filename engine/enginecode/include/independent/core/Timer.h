/** \file Timer.h
*/
#pragma once

#include "systems/system.h"
namespace Engine {

	class Timer : public System
	{
	private:
		float m_Time;
	public:
		Timer(float time = 0.0f)
			: m_Time(time) {}
		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	
		virtual void start(SystemSignal init = SystemSignal::None, ...) override;
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override;
	};
}