/**
\class OpenGLClearDepthColourBufferCommand, OpenGLSetClearColourCommand, OpenGLSetDepthTestLessCommand and OpenGLSetBackfaceCullingCommand classes
*/

#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine {
	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLClearDepthColourBufferCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};	//!<Constructor for clearing depth colour
		void action() override;	//!<Virtual action function
	};

	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}	//!<Constructor for setting clear colour
		void action() override;	//!<Virtual action function
	};

	class OpenGLSetDepthTestLessCommand : public RenderCommand
	{
	public:
		OpenGLSetDepthTestLessCommand(bool enabled) {};	//!<Constructor for setting depth test
		void action() override;	//!<Virtual action function
	};

	class OpenGLSetBackfaceCullingCommand : public RenderCommand
	{
	public:
		OpenGLSetBackfaceCullingCommand(bool enabled) {};	//!<Constructor for setting backface culling
		void action() override;	//!<Virtual action function
	};
}