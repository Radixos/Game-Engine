#pragma once

#include <include\independent\Rendering\Material.h>
#include <engine.h>

#include "GameObject.h"

namespace Engine {
	class MaterialComponent : public Component
	{
	private:
		std::shared_ptr<Material> m_material;
	public:
		MaterialComponent(const std::shared_ptr<Material>& material) : m_material(material) {}
		inline std::shared_ptr<Material> getMaterial() { return m_material; }
		void receiveMessage(const ComponentMessage& msg) override
		{
			switch (msg.m_msgType)
			{
			case ComponentMessageType::UniformSet:
				std::pair<std::string, void*> data = std::any_cast<std::pair<std::string, void*>>(msg.m_msgData);
				m_material->setDataElement(data.first, data.second);
				return;
			}
		}
	};

	class PositionComponent : public Component
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
			m_scale = glm::scale(m_scaleVec);
			m_model = m_translation * m_rotation * m_scale;
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
			//ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
		void onAttach(GameObject* owner) override
		{
			m_owner = owner;
			std::pair<std::string, void*> data("u_model", (void*)&m_model[0][0]);
			//ComponentMessage msg(ComponentMessageType::UniformSet, data);
			sendMessage(msg);
		}
	};
}