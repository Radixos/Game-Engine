/**
\class OpenGLTexture class
*/
#pragma once

#include "Rendering/Texture.h"

namespace Engine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& filepath);	//!<Constructor using filepath
		//OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData);	//!<Constructor using parameters
		unsigned int getWidth() const override { return m_width; }	//!<Function for returning width
		unsigned int getHeight() const override { return m_height; };	//!<Function for returning height
		unsigned int getChannels() const override { return m_channels; };	//!<Function for returning channels
		unsigned int getSlot() const override { return m_textureSlot; };	//!<Function for returning texture slot
	private:
		static unsigned int s_textureSlot;

		const std::string& m_filepath;
		int m_width;	//was unsigned
		int m_height;	//was unsigned
		unsigned int m_textureSlot;
		unsigned int m_texID;
		int m_channels;
	};
}
