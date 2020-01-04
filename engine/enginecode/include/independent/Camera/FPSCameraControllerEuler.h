/** \class FPSCameraControllerEuler class
*/

#pragma once

#include "CameraController.h"
#include "PerspectiveCamera3D.h"
#include "Event/EventSubclass.h"

namespace Engine {
	class FPSCameraControllerEuler : public CameraController
	{
	private:
		std::shared_ptr<PerspectiveCamera3D> m_camera;
		glm::mat4 m_view;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;
		float m_yaw;
		float m_pitch;
		float m_translationSpeed = 2.0f;
		float m_rotationSpeed = 2.0f;
		glm::vec2 m_lastMousePosition;

		void updateView();	//!<Declaring updateView function
	public:
		FPSCameraControllerEuler();	//!<Default constructor
		void init(float fov = 45.f, float aspectRatio = 4.0f / 3.0f, float nearClip = 0.1f, float farClip = 100.f) override {};	//Added {}???	//!<Overrided init function
		std::shared_ptr<Camera> getCamera() override { return m_camera; }	//!<Overrided getCamera function for returning the camera
		void onUpdate(float timestep) override;	//!<Overrided onUpdate function
		void onEvent(Event& e) override;	//!<Overrided onEvent function
		void onResize() override {};	//!<Overrided onResize function
		bool onMouseButton(MouseButtonPressed& e);	//!<Declaring onMouseButton function
	};
}