#pragma once

#include <memory>
#include "Camera.h"

namespace Engine {
	class CameraController
	{
	public:
		virtual void init(float, float, float, float) = 0;
		virtual std::shared_ptr<Camera> getCamera() = 0;
		virtual void onUpdate(float timestep) = 0;
		virtual void onEvent(Event& e) = 0;
		virtual void onResize() = 0;
	};
}