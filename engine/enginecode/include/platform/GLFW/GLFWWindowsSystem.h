/**
/class GLFWWindowsSystem class
*/

#pragma once

#include "windows/WindowSystem.h"
#include "../include/GLFW/glfw3.h"
#include "systems/Log.h"

namespace Engine {
	class GLFWWindowsSystem : public WindowSystem
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override;	//!<Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) override;	//!<Start the system
	};
}