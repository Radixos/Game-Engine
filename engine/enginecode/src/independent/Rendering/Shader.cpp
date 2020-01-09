/**
\file Shader.cpp
*/
#include "engine_pch.h"
#include "include\independent\Rendering\Shader.h"
#include "Rendering/RenderAPI.h"
#include "systems/Log.h"
#include "include/platform/OpenGL/OpenGLShader.h"

namespace Engine {
	Shader* Engine::Shader::create(const std::string& filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
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