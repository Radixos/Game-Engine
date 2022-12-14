/**
\file OrthographicCamera2D.cpp
*/
#include "engine_pch.h"
#include "include/independent/Camera/OrthographicCamera2D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {
	void OrthographicCamera2D::updateView()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_position, 1.f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_view = rotate * translate;

		m_viewProjection = m_projection * m_view;
	}

	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top)
	{
		glm::mat4 m_projection = glm::ortho(left, right, bottom, top);
		glm::mat4 m_view = glm::mat4(1.f);
		glm::mat4 m_viewProjection = m_projection * m_view;
	}
	void OrthographicCamera2D::reset(float left, float right, float bottom, float top)
	{
		glm::mat4 m_projection = glm::ortho(left, right, bottom, top);
		glm::mat4 m_view = glm::mat4(1.f);
		glm::mat4 m_viewProjection = m_projection * m_view;
	}
}