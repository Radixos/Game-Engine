/** \class CameraController virtual class
*/

#pragma once

#include <memory>
#include "Camera.h"
#include "Event/Event.h"

namespace Engine {
	class CameraController
	{
	public:
		virtual void init(float, float, float, float) = 0;	//!<Virtual init
		virtual std::shared_ptr<Camera> getCamera() = 0;	//!<Virtual function for getCamera
		virtual void onUpdate(float timestep) = 0;	//!<Virtual onUpdate function
		virtual void onEvent(Event& e) = 0;	//!<Virtual onEvent function
		virtual void onResize() = 0;	//!<Virtual onResize function
	};
}