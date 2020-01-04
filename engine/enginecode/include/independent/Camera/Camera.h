/** \class Camera base class
*/

#pragma once
#include <glm/glm.hpp>

namespace Engine {
	class Camera
	{
	protected:
		glm::mat4 m_projection;	//!<Declaring projection
		glm::mat4 m_view;	//!<Declaring view
		glm::mat4 m_viewProjection;	//!<Declaring viewProjection
	public:
		virtual void updateView() = 0;	//!<Virtual function for updateView (for future overrides)
		const glm::mat4& getProjection() { return m_projection; }	//!<Declaring and defining function for returning the projection
		const glm::mat4& getView() { return m_view; }	//!<Declaring and defining function for returning the view
		const glm::mat4& getViewProjection() { return m_viewProjection; }	//!<Declaring and defining function for returning the viewProjection
	};
}