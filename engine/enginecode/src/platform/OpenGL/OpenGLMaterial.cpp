/** \file OpenGLMaterial.h
*/

#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLMaterial.h"
#include <variant>

namespace Engine {
	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		m_shader = shader;
		shader->bind();
		VAO->bind();
	}

	/*OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO)
	{
		m_shader = shader;
		shader->bind();
		VBO->bind();
	}*/

	void OpenGLMaterial::init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		m_shader = shader;
		shader->bind();
		VAO->bind();
	}

	void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = shader;
		shader->bind();
	}

	void OpenGLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{
		std::variant<std::shared_ptr<VertexArray>,std::shared_ptr<VertexBuffer>>(m_geometry) = geometry;
	}

	void OpenGLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{
		std::map<std::string, void*>(m_data) = data;
	}

	void OpenGLMaterial::setDataElement(const std::string& dataName, void* data)
	{

	}

	void OpenGLMaterial::setVertexData(float* vertices, unsigned int size, unsigned int offset)
	{

	}
}