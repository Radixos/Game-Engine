/** \file OpenGLSetClearColourCommand.cpp
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLSetClearColourCommand.h"
#include <glad\glad.h>

namespace Engine
{
	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);
	}
}