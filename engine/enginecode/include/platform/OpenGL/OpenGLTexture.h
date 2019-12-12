#pragma once

#include "Rendering/Texture.h"

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& filepath);
		OpenGLTexture(unsigned int width,unsigned int height, unsigned int channels, unsigned char* textData);
		unsigned int getWidth() const override { return m_width; }
		unsigned int getHeight() const override { return m_height; };
		unsigned int getChannels() const override { return m_channels; };
		unsigned int getSlot() const override { return m_textureSlot; };
	private:
		static unsigned int s_textureSlot;

		std::string& m_filepath;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_textureSlot;
		unsigned int m_texID;
		int m_channels;
	};
}
