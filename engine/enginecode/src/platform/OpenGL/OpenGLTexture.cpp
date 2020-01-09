/**
\file OpenGLTexture.cpp
*/
#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Engine {

	unsigned int OpenGLTexture::s_textureSlot = 0;

	OpenGLTexture::OpenGLTexture(const std::string& filepath)
		: m_filepath(filepath)
	{
		glGenTextures(1, &m_texID);
		
		m_textureSlot = s_textureSlot;
		s_textureSlot++;

		glActiveTexture(GL_TEXTURE0 + m_textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* texData = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_channels, 0);
		if (m_channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		else if (m_channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		else if (m_channels == 1) glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
		else return;

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(texData);
	}

	//OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData)
		//: m_width(width), m_height(height), m_channels(channels)
	//{
		//glBindVertexArray(m_texID);
		//vertexBuffer->bind();
		//m_vertexBuffer = vertexBuffer;

		//unsigned int index = 0;
		//auto layout = vertexBuffer->GetLayout();
		//for (auto element : layout)
		//{
		//	glEnableVertexAttribArray(index);
		//	glVertexAttribPointer(index,
		//		ShaderDataTypeComponentCount(element.m_dataType),
		//		ShaderDataTypeToOpenGLType(element.m_dataType),
		//		GL_FALSE,
		//		layout.GetStride(),
		//		(void*)element.m_offset); // (pos 0 (pos), 3 floats, float, not normalised, 6 float between each data line, start at 0)

		//	/*ENG_CORE_INFO("{0} {1} {2} {3} {4}", index,
		//		ShaderDataTypeComponentCount(element.m_dataType),
		//		ShaderDataTypeToOpenGLType(element.m_dataType),
		//		layout.GetStride(),
		//		(void*)element.m_offset
		//		);*/
		//	index++;
		//}
		/*glGenTextures(1, &m_letterTexture);
		glActiveTexture(GL_TEXTURE0);
		m_textureSlots[0] = 0;
		glBindTexture(GL_TEXTURE_2D, m_letterTexture);*/
	//}

	/*unsigned int OpenGLTexture::getWidth() const
	{
		return 0;
	}

	unsigned int OpenGLTexture::getHeight() const
	{
		return 0;
	}

	unsigned int OpenGLTexture::getChannels() const
	{
		return 0;
	}

	unsigned int OpenGLTexture::getSlot() const
	{
		return 0;
	}*/
}