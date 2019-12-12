/** /class Texture
	An interface class for creating API specific textures.
*/
#pragma once

#include <sstream>

namespace Engine
{
	class Texture
	{
	public:
		virtual unsigned int getWidth() const = 0;	//!<Get the width of the texture
		virtual unsigned int getHeight() const = 0;	//!<Get the height of the texture
		virtual unsigned int getChannels() const = 0;	//!<Get the number of channels of the texture (1 = Greyscale, 3 = RGB, 4 = RGBA)
		virtual unsigned int getSlot() const = 0;	//!<Get the memory slot in the GPU where the texture resides

		static Texture* createFromFile(const std::string& filepath);	//!<Create an API specific texture
		static Texture* createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* texData);	//!<Create an API specific texture
	};
}
