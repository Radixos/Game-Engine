/** \file OpenGLMaterial.h
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLMaterial.h"

namespace Engine {
	void OpenGLMaterial::init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{

	}

	void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{

	}

	void OpenGLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{

	}

	void OpenGLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{

	}

	void OpenGLMaterial::setDataElement(const std::string& dataName, void* data)
	{

	}

	void OpenGLMaterial::setVertexData(float* vertices, unsigned int size, unsigned int offset)
	{

	}
}