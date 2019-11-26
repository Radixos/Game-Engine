/** \file OpenGLBasicRenderer.h
*/
#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine {
	class OpenGLBasicRenderer : RenderCommand
	{
	public:
		void actionCommand(RenderCommand* command);
	};
}