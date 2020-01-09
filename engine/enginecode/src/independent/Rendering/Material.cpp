/**
\file Material.cpp
*/

#include "engine_pch.h"
#include "include/independent/Rendering/Material.h"
#include "Rendering/RenderAPI.h"
#include "systems/Log.h"
#include "include/platform/OpenGL/OpenGLMaterial.h"

namespace Engine {
	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLMaterial(shader, VAO);
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API");
		}
		return nullptr;
	}

	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			//return new OpenGLMaterial(shader, VBO);
			ENG_CORE_ERROR("Can not create material using VBO.");
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