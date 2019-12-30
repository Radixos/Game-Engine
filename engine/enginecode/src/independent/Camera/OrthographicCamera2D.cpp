#include "engine_pch.h"
#include "include/independent/Camera/OrthographicCamera2D.h"

namespace Engine {
	void OrthographicCamera2D::updateView()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_position, 1.f));
		glm::mat4 rotate = glm::rotate(glm::mat4(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		m_view = translate * rotate;

		m_viewProjection = m_projection * m_view;
	}

	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top)
	{
		glm::mat4 m_projection = glm::ortho(left, right, bottom, top);
		glm::mat4 m_view = glm::mat4(1.f);
		glm::mat4 m_viewProjection = m_projection * m_view;
	}
}