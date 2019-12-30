#include "Camera/FreeOrthoCameraController2D.h"
#include "include/platform/GLFW/InputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"

namespace Engine {
	FreeOrthoCameraController2D::FreeOrthoCameraController2D()
	{

	}

	void FreeOrthoCameraController2D::init(float left, float top, float width, float height)
	{

	}

	void Engine::FreeOrthoCameraController2D::onUpdate(float timestep)
	{
		//Movement

		if (InputPoller::isKeyPressed(KEY_W))
		{
			m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_S))
		{
			m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
		}

		//Rotation

		if (InputPoller::isKeyPressed(KEY_Q))
		{
			m_rotation -= timestep * m_rotationSpeed;
			if (m_rotation > 100.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -100.0f) m_rotation += 360.0f;
		}
		if (InputPoller::isKeyPressed(KEY_E))
		{
			m_rotation += timestep * m_rotationSpeed;
			if (m_rotation > 100.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -100.0f) m_rotation += 360.0f;
		}
	}
}