#include "engine_pch.h"
#include "Rendering/RenderCommand.h"
#include <include\independent\Rendering\RenderAPI.h>
#include "systems/Log.h"

namespace Engine
{

	RenderCommand* RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			//return new OpenGLSetBackfaceCullingCommand(enabled);
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