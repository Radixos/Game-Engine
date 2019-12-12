#include "engine_pch.h"
#include "include/independent/Rendering/Texture.h"
#include "Rendering/RenderAPI.h"
#include "systems/Log.h"
#include "include/platform/OpenGL/OpenGLTexture.h"

namespace Engine {
	Texture* Texture::createFromFile(const std::string & filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API");
		}
		return nullptr;
	}

	Texture * Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		return nullptr;
	}
}