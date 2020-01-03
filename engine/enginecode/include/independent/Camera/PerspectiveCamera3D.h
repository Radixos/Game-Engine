/** \class PerspectiveCamera3D class
*/

#pragma once

#include "Camera.h"

namespace Engine {
	class PerspectiveCamera3D : public Camera
	{
	private:
		glm::vec3 m_position = glm::vec3(0.f);
		//glm::quat m_orientation;
		void updateView() override;	//!<Overrided updateView function
	public:
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip);	//!<Constructor for PerspectiveCamera3D
		void reset(float fov, float aspectRatio, float nearClip, float farClip);	//Should there be anythig done with it or was the idea the same as with constructor?
		inline glm::vec3 getPosition() { return m_position; }	//!<Inline getPosition function definition for returning the position
		//inline glm::quat getOrientation() { return m_orientation; }
		void setView(const glm::mat4& view) { m_view = view; m_viewProjection = m_projection * m_view; }	//!<Definition of setView function for setting the view and viewProjection
		//void setPosition(const glm::vec3& position) { m_position = position; updateView(); }
		//void setOrientation(const glm::quat& orientation) { m_orientation = orientation; updateView(); }
		//void setPositionAndOrientation(const glm::vec3& position, const glm::quat& orientation)
		//{ m_position = position, m_orientation = orientation; updateView(); }
	};
}