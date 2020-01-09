/**
\file FPSCameraControllerEuler.cpp
*/
#include "engine_pch.h"
#include "include/independent/Camera/FPSCameraControllerEuler.h"
#include "include/independent/Camera/Camera.h"
#include "include/platform/GLFW/InputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"
#include "include/independent/Event/EventDispatcher.h"
#include "glm/ext/matrix_transform.hpp"

namespace Engine {
	void FPSCameraControllerEuler::updateView()
	{
		//Calculate the new forward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(forward);

		//Re-calculate the right and up vector
		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		//Re-calculate view matrix
		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	FPSCameraControllerEuler::FPSCameraControllerEuler()
	{

	}

	void FPSCameraControllerEuler::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W)) { m_position += m_forward * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_S)) { m_position -= m_forward * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_A)) { m_position -= m_right * m_translationSpeed * timestep; }
		if (InputPoller::isKeyPressed(KEY_D)) { m_position += m_right * m_translationSpeed * timestep; }
	
		if (InputPoller::isMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			glm::vec2 currentMousePosition = InputPoller::getMousePosition();
			glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition;

			m_yaw += mouseDelta.x * m_rotationSpeed * timestep;
			m_pitch -= mouseDelta.y * m_rotationSpeed * timestep;
		
			//Constrain pitch
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;

			m_lastMousePosition = currentMousePosition;
		}
	}

	void FPSCameraControllerEuler::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonPressed>(std::bind(&FPSCameraControllerEuler::onMouseButton, this, std::placeholders::_1));
	}

	bool FPSCameraControllerEuler::onMouseButton(MouseButtonPressed& e)
	{
		if (e.getButton() == MOUSE_BUTTON_LEFT)
			m_lastMousePosition = InputPoller::getMousePosition();

		return true;
	}
}