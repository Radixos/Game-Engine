/** \file OpenGLBasicRenderer.cpp
*/
#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLBasicRenderer.h"

namespace Engine {
	void OpenGLBasicRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}
}