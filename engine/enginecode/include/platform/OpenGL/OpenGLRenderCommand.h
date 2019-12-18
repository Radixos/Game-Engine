#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine {
	class ClearDepthColourBufferCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		ClearDepthColourBufferCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
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

	class setDepthTestLessCommand : public RenderCommand
	{
	public:
		setDepthTestLessCommand(bool enabled) {};
		void action() override;
	};

	class setBackfaceCullingCommand : public RenderCommand
	{
	public:
		setBackfaceCullingCommand(bool enabled) {};
		void action() override;
	};
}