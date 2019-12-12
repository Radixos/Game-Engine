/** \file VertexArray.cpp
*/
#include "engine_pch.h"
#include "include/independent/Rendering/VertexArray.h"
#include "include/platform/OpenGL/OpenGLVertexArray.h"

#include "Rendering/RenderAPI.h"
#include "systems/Log.h"

namespace Engine {

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API");
		}
		return nullptr;
	}
}
