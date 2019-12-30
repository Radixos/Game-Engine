#include "engine_pch.h"
#include "include/independent/Camera/FPSCameraControllerEuler.h"
#include "include/independent/Camera/Camera.h"
#include "include/platform/GLFW/InputPoller.h"
#include "include/platform/GLFW/GLFWCodes.h"

namespace Engine {
	/*void FPSCameraControllerEuler::updateView()
	{

	}*/

	void FPSCameraControllerEuler::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W)) { m_position += m_forward * m_translationSpeed * timestep; }
	}

	/*void FPSCameraControllerEuler::updateView()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_position, 1.f));
		glm::mat4 rotate = glm::rotate(glm::mat4(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		m_view = translate * rotate;

		m_viewProjection = m_projection * m_view;
	}*/
}