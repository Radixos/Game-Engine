#include "engine_pch.h"
#include "Rendering/RenderCommand.h"
#include <include\independent\windows\RenderAPI.h>

RenderCommand* RenderCommand::setBackfaceCullingCommand(bool enabled)
{
	switch (RenderAPI::getApi())
	{
	case RenderAPI::API::None:
		ENG_FATAL("Lack of graphics API not supported.");
		break;
	case RenderAPI::API::OpenGL:
		return new OpenGLSetBackfaceCullingCommand(enabled);
		break;
	case RenderAPI::API::Direct3D:
		ENG_FATAL("Direct3D not supported.");
		break;
	default:
		ENG_FATAL("Unknown graphics API.");
	}
}