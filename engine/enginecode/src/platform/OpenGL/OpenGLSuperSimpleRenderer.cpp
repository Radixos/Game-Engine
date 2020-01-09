/**
\file OpenGLSuperSimpleRenderer.cpp
*/
#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLSuperSimpleRenderer.h"
#include <glad\glad.h>

namespace Engine {
	void OpenGLSuperSimpleRenderer::actionCommand(RenderCommand* command)
	{

	}

	void OpenGLSuperSimpleRenderer::submit(const std::shared_ptr<Material>& material)
	{
		//Bind the shader
		auto shader = material->getShader();
		shader->bind();

		//Bind the geometry
		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		//Set each uniform in the data
		auto uniformData = material->getData();
		for (auto dataPair : uniformData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}

		//Issue a draw call
		glDrawElements(GL_TRIANGLES, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}
}