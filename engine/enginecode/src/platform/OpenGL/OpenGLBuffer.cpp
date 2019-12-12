#include "engine_pch.h"

#include "include/platform/OpenGL/OpenGLBuffer.h"

#include <../include/glad/glad.h>

namespace Engine {

	//////////////////////////////////////OpenGLVertexBuffer//////////////////////////////////////

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

	//////////////////////////////////////OpenGLIndexBuffer//////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	Engine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void Engine::OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void Engine::OpenGLIndexBuffer::unBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}