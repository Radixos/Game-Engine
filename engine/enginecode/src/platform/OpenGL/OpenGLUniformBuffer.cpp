#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLUniformBuffer.h"
#include <glad\glad.h>

namespace Engine {
	OpenGLUniformBuffer::OpenGLUniformBuffer(unsigned int id, unsigned int size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_UNIFORM_BUFFER, id);
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, id, 0, size);	//After m_binding point was ", id, 0, size"
	}

	void OpenGLUniformBuffer::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
	}

	void OpenGLUniformBuffer::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName)
	{
		unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader->id(), blockName.c_str());
		glUniformBlockBinding(shader->id(), uniformBlockIndex, m_bindingPoint);
	}

	void OpenGLUniformBuffer::setData(unsigned int offset, unsigned int size, void* data)
	{

	}

	UniformBuffer* OpenGLUniformBuffer::create(unsigned int size, UniformBufferLayout& layout)
	{
		return nullptr;
	}
}