/** \class OrthographicCamera2D class
*/

#pragma once

#include "Camera.h"

namespace Engine {
	class OrthographicCamera2D : public Camera
	{
	private:
		glm::vec2 m_position = glm::vec2(0.f);
		float m_rotation = 0.f;

		void updateView() override;	//!<Overrided updateView function
	public:
		OrthographicCamera2D(float left, float right, float bottom, float top);	//!<Constructor for the 2d orthographic camera
		void reset (float left, float right, float bottom, float top);	//Should there be anythig done with it or was the idea the same as with constructor?
		inline glm::vec2 getPosition() const { return m_position; }	//!<Inline getPosition function definition for returning the position
		inline float getRotation() const { return m_rotation; }//!<Inline getRotation function definition for returning the rotation
		
		void setPosition(const glm::vec2& position) { m_position = position; updateView(); }	//!<Definition of setPosition function for setting the position and updating the view
		void setRotation(float rotation) { m_rotation = rotation; updateView(); }	//!<Definition of setRotation function for setting the rotation and updating the view
		void setPositionRotation(const glm::vec2& position, float rotation)
		{ m_position = position; m_rotation = rotation; updateView(); }	//!<Definition of setPositionRotation function for setting the position, rotation and updating the view
	};
}