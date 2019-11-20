#include "engine_pch.h"
#include "Rendering/RenderCommand.h"
#include "systems/Log.h"
#include "include/independent/Rendering/RenderAPI.h"

RenderCommand* RenderCommand::setBackfaceCullingCommand(bool enabled)
{
	switch (RenderAPI::getApi())
	{
	case RenderAPI::API::None:
		ENG_CORE_WARN("Lack of graphics API not supported.");	//To change warn on fatal (work on fatal in log.h)
		break;
	case RenderAPI::API::OpenGL:
		return new OpenGLSetBackfaceCullingCommand(enabled);
		break;
	case RenderAPI::API::Direct3D:
		ENG_CORE_WARN("Direct3D not supported.");
		break;
	default:
		ENG_CORE_WARN("Unknown graphics API.");
	}
}