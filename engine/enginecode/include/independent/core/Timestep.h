#pragma once

namespace Engine {

	class Timestep
	{
	private:
		float m_Time;
	public:
		Timestep(float time = 0.0f)
			: m_Time(time) {}

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	};
}