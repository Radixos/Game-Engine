#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>

Engine::OpenGLTexture::OpenGLTexture(const std::string & filepath)
{
	
}

Engine::OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * textData)
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
	/*glGenTextures(1, &m_letterTexture);
	glActiveTexture(GL_TEXTURE0);
	m_textureSlots[0] = 0;
	glBindTexture(GL_TEXTURE_2D, m_letterTexture);*/
}

unsigned int Engine::OpenGLTexture::getWidth() const
{
	return 0;
}

unsigned int Engine::OpenGLTexture::getHeight() const
{
	return 0;
}

unsigned int Engine::OpenGLTexture::getChannels() const
{
	return 0;
}

unsigned int Engine::OpenGLTexture::getSlot() const
{
	return 0;
}