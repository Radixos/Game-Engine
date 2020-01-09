/**
\file for indexBuffer and vertexBuffer
*/
#include "engine_pch.h"

#include "Rendering/RenderAPI.h"
#include "Rendering/Buffer.h"
//#include "include/platform/OpenGL/OpenGLIndexBuffer"
#include "systems/Log.h"
#include "include/platform/OpenGL/OpenGLVertexBuffer.h"
#include "include/platform/OpenGL/OpenGLIndexBuffer.h"

namespace Engine {

	IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int size)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			break;
		case RenderAPI::API::Direct3D:
			ENG_CORE_ERROR("Direct3D not supported.");
			break;
		default:
			ENG_CORE_ERROR("Unknown graphics API");
		}
		return nullptr;
	}

	VertexBuffer* VertexBuffer::create(float* vertices, unsigned int size, BufferLayout& layout)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			ENG_CORE_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size, layout);
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