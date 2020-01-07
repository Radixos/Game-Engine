/**
/class WindowSystem class
*/

#pragma once

#include "systems/system.h"

namespace Engine {
	class WindowSystem : public System
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...) = 0;	//!<Start the system
		virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0;	//!<Start the system
	};
}