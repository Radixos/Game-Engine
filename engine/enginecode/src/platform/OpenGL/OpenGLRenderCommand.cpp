/**
\file OpenGLRenderCommands.cpp
*/
#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLRenderCommand.h"
#include <glad\glad.h>

namespace Engine {
	void OpenGLClearDepthColourBufferCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);	//(0, 0, 1, 1) - blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);	//(0, 0, 1, 1) - blue
	}

	void OpenGLSetDepthTestLessCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	void OpenGLSetBackfaceCullingCommand::action()
	{
		if (m_enabled)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void OpenGLSetOneMinusAlphaBlending::action()
	{
		if (m_enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}
}