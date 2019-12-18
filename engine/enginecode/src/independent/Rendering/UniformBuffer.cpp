#include "engine_pch.h"
#include "Rendering/UniformBuffer.h"
#include <include\independent\Rendering\RenderAPI.h>
#include "include/platform/OpenGL/OpenGLUniformBuffer.h"
#include "systems/Log.h"

namespace Engine {
	UniformBuffer* UniformBuffer::create(unsigned int size, UniformBufferLayout& layout)
	{
		{
			switch (RenderAPI::getApi())
			{
			case RenderAPI::API::None:
				ENG_CORE_ERROR("Lack of graphics API not supported.");
				break;
			case RenderAPI::API::OpenGL:
				OpenGLUniformBuffer(size, layout);
				break;
			case RenderAPI::API::Direct3D:
				ENG_CORE_ERROR("Direct3D not supported.");
				break;
			default:
				ENG_CORE_ERROR("Unknown graphics API.");
			}
			return nullptr;
		}
	}
}