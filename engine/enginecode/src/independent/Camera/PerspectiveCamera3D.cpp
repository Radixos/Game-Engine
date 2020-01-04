#include "engine_pch.h"
#include "include/independent/Camera/PerspectiveCamera3D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {
	/*void PerspectiveCamera3D::updateView()
	{
		
	}*/

	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
	}
}