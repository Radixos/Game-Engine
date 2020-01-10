/**
\file FreeOrthoCameraController2D.cpp
*/
#include "engine_pch.h"

#include "Camera/FreeOrthoCameraController2D.h"
#include "include/platform/GLFW/InputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"

namespace Engine {
	FreeOrthoCameraController2D::FreeOrthoCameraController2D()
	{

	}

	void FreeOrthoCameraController2D::init(float left, float top, float width, float height)
	{
		m_camera.reset(new OrthographicCamera2D(left, width + left, top + height, height));
		m_camera->setPositionRotation(m_position, m_rotation);
	}

	void Engine::FreeOrthoCameraController2D::onUpdate(float timestep)
	{
		//Movement

		if (InputPoller::isKeyPressed(KEY_I))
		{
			m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_camera->setPositionRotation(m_position, m_rotation);
		}
		if (InputPoller::isKeyPressed(KEY_K))
		{
			m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_camera->setPositionRotation(m_position, m_rotation);
		}
		if (InputPoller::isKeyPressed(KEY_J))
		{
			m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_camera->setPositionRotation(m_position, m_rotation);
		}
		if (InputPoller::isKeyPressed(KEY_L))
		{
			m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * timestep;
			m_camera->setPositionRotation(m_position, m_rotation);
		}

		//Rotation

		if (InputPoller::isKeyPressed(KEY_Q))
		{
			m_rotation += timestep * m_rotationSpeed;
			if (m_rotation > 100.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -100.0f) m_rotation += 360.0f;
			m_camera->setPositionRotation(m_position, m_rotation);
		}
		if (InputPoller::isKeyPressed(KEY_E))
		{
			m_rotation -= timestep * m_rotationSpeed;
			if (m_rotation > 100.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -100.0f) m_rotation += 360.0f;
			m_camera->setPositionRotation(m_position, m_rotation);
		}
	}
}