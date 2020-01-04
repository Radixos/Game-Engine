#include "engine_pch.h"
#include "Rendering/RenderCommand.h"
#include <include\independent\Rendering\RenderAPI.h>
#include "systems/Log.h"
#include <glad\glad.h>
#include "include/platform/OpenGL/OpenGLRenderCommand.h"

namespace Engine
{
	RenderCommand* RenderCommand::ClearDepthColourBufferCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLClearDepthColourBufferCommand(0, 0, 1, 1);	//(0, 0, 1, 1) - blue
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API.");
		}
		return nullptr;
	}

	RenderCommand* RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetClearColourCommand(0, 0, 1, 1);	//(0, 0, 1, 1) - blue
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API.");
		}
		return nullptr;
	}

	RenderCommand* RenderCommand::setDepthTestLessCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetDepthTestLessCommand(enabled);
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API.");
		}
		return nullptr;
	}

	RenderCommand* RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetBackfaceCullingCommand(enabled);
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