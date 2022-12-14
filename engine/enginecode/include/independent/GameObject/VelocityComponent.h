/**
\class VelocityComponent class
*/

#pragma once

#include <any>
#include <glm/glm.hpp>
#include "GameObject.h"

namespace Engine {
	class VelocityComponent : public Component	//!<VelocityComponent class publicly inhariting from Component
	{
	private:
		glm::vec3 m_linear;
		glm::vec3 m_angular;
	public:
		VelocityComponent(glm::vec3 linear, glm::vec3 angular) : m_linear(linear), m_angular(angular) {}
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::VelocitySetLinear:
			{
				glm::vec3 linear = std::any_cast<glm::vec3>(msg.m_msgData);
				m_linear = linear;
				return;
			}
			case ComponentMessageType::VelocitySetAngular:
			{
				glm::vec3 angular = std::any_cast<glm::vec3>(msg.m_msgData);
				m_angular = angular;
				return;
			}
			}
		}
		void onUpdate(float timestep) override
		{
			std::pair<glm::vec3, glm::vec3> data(m_linear * timestep, m_angular * timestep);
			sendMessage(ComponentMessage(ComponentMessageType::PositionIntegrate, std::any(data)));
		}
	};
}