/**
\class PositionComponent class
*/

#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"
#include "MaterialComponent.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Engine {
	class PositionComponent : public Component	//!<PositionComponent class publicly inhariting from Component
	{
	private:
		glm::mat4 m_model;
		glm::mat4 m_translation;
		glm::mat4 m_rotation;
		glm::mat4 m_scale;
		glm::vec3 m_transVec;
		glm::vec3 m_rotVec;
		glm::vec3 m_scaleVec;
		inline void calculateModel() {
			m_translation = glm::translate(glm::mat4(1.0f), m_transVec);
			m_rotation = glm::toMat4(glm::quat(m_rotVec));
			m_scale = glm::scale(m_model, m_scaleVec);
			m_model = m_scale * m_translation * m_rotation;
		}
	public:
		PositionComponent(glm::vec3 trans, glm::vec3 rot, glm::vec3 scale) :
			m_transVec(trans), m_rotVec(rot), m_scaleVec(scale),
			m_model(glm::mat4(1.0f))
		{
			m_rotVec.x = glm::radians(m_rotVec.x);
			m_rotVec.y = glm::radians(m_rotVec.y);
			m_rotVec.z = glm::radians(m_rotVec.z);
			calculateModel();
		};
		inline std::shared_ptr<glm::mat4> getTransform() { return std::make_shared<glm::mat4>(m_model); }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::PositionSet:
			{
				glm::vec3 pos = std::any_cast<glm::vec3>(msg.m_msgData);
				m_transVec = pos;
				calculateModel();
				return;
			}
			case ComponentMessageType::PositionIntegrate:
			{
				std::pair<glm::vec3, glm::vec3> vel = std::any_cast<std::pair<glm::vec3, glm::vec3>>(msg.m_msgData);

				m_transVec += vel.first;
				m_rotVec.x += glm::radians(vel.second.x);
				m_rotVec.y += glm::radians(vel.second.y);
				m_rotVec.z += glm::radians(vel.second.z);
				calculateModel();
				return;
			}
			}
		}
		void onUpdate(float timestep) override
		{
			std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
		void onAttach(GameObject* owner) override
		{
			m_owner = owner;
			std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
			ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
	};
}