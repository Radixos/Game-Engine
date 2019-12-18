#include "engine_pch.h"
#include "include\independent\Rendering\Renderer.h"
#include "include/platform/OpenGL/OpenGLBasicRenderer.h"
#include "include/platform/OpenGL/OpenGLBasicTextRenderer.h"
#include <include\independent\Rendering\RenderAPI.h>
#include <engine.h>

namespace Engine {
	Renderer* Renderer::createBasic3D()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLBasicRenderer();
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API.");
		}
		return nullptr;
	}

	Renderer* Renderer::createBasicTextRenderer2D()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLBasicTextRenderer();
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