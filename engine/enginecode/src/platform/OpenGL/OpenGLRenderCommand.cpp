#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLRenderCommand.h"
#include <glad\glad.h>

namespace Engine {
	void ClearDepthColourBufferCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);	//(0, 0, 1, 1) - blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);	//(0, 0, 1, 1) - blue
	}

	void setDepthTestLessCommand::action()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void setBackfaceCullingCommand::action()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
}