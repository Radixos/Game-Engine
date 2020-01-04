#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine {
	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLClearDepthColourBufferCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		void action() override;
	};

	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}
		void action() override;
	};

	class OpenGLSetDepthTestLessCommand : public RenderCommand
	{
	public:
		OpenGLSetDepthTestLessCommand(bool enabled) {};
		void action() override;
	};

	class OpenGLSetBackfaceCullingCommand : public RenderCommand
	{
	public:
		OpenGLSetBackfaceCullingCommand(bool enabled) {};
		void action() override;
	};
}