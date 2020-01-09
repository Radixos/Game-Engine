/**
\file OpenGLVertexArray.cpp
*/
#include "engine_pch.h"

#include <glad/glad.h>

#include "include/platform/OpenGL/OpenGLVertexArray.h"
#include "include/platform/OpenGL/OpenGLIndexBuffer.h"
#include "systems/Log.h"

namespace Engine {

	static unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Int:		return GL_INT;
	case ShaderDataType::Int2:		return GL_INT;
	case ShaderDataType::Int3:		return GL_INT;
	case ShaderDataType::Int4:		return GL_INT;
	case ShaderDataType::Float:		return GL_FLOAT;
	case ShaderDataType::Float2:	return GL_FLOAT;
	case ShaderDataType::Float3:	return GL_FLOAT;
	case ShaderDataType::Float4:	return GL_FLOAT;
	case ShaderDataType::Mat3:		return GL_FLOAT;
	case ShaderDataType::Mat4:		return GL_FLOAT;
	case ShaderDataType::Bool:		return GL_BOOL;
	}
	return 0;
}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_id);
		glBindVertexArray(m_id);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_id);
		m_vertexBuffer->bind();
		m_indexBuffer->bind();
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
		m_vertexBuffer->unBind();
		m_indexBuffer->unBind();
	}

	void OpenGLVertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_id);
		vertexBuffer->bind();
		m_vertexBuffer = vertexBuffer;

		unsigned int index = 0;
		auto layout = vertexBuffer->GetLayout();
		for (auto element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				ShaderDataTypeComponentCount(element.m_dataType),
				ShaderDataTypeToOpenGLType(element.m_dataType),
				GL_FALSE,
				layout.GetStride(),
				(void*)element.m_offset); // (pos 0 (pos), 3 floats, float, not normalised, 6 float between each data line, start at 0)

			/*ENG_CORE_INFO("{0} {1} {2} {3} {4}", index,
				ShaderDataTypeComponentCount(element.m_dataType),
				ShaderDataTypeToOpenGLType(element.m_dataType),
				layout.GetStride(),
				(void*)element.m_offset
				);*/
			index++;
		}
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // (pos 0 (pos), 3 floats, float, not normalised, 6 float between each data line, start at 0)
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3)); // (pos 1 (colour), 3 floats, float, not normalised, 6 float between each data line, start at 3)

	}

	void OpenGLVertexArray::setindexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_id);
		indexBuffer->bind();

		m_indexBuffer = indexBuffer;
	}
}