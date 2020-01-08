#include "engine_pch.h"

#include "include/platform/OpenGL/OpenGLVertexBuffer.h"

#include <../include/glad/glad.h>

namespace Engine {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size, BufferLayout& layout) : m_Layout(layout)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	Engine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void Engine::OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void Engine::OpenGLVertexBuffer::unBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}