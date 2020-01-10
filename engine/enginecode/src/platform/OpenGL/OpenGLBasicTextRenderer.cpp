/**
\file OpenGLBasicTextRenderer.cpp
*/
#include "engine_pch.h"
#include "include/platform/OpenGL/OpenGLBasicTextRenderer.h"

#include <glad\glad.h>
namespace Engine {
	void OpenGLBasicTextRenderer::actionCommand(RenderCommand* command)
	{
		command->action();
		delete command;
	}

	void OpenGLBasicTextRenderer::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		/*auto uniforms = material->getData();
		for (auto it = uniforms.begin(); it != uniforms.end(); ++it)
		{
			shader->uploadData(it->first, it->second);
		}*/

		auto perDrawData = material->getData();
		for (auto dataPair : perDrawData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}
		glDrawElements(GL_QUADS, geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

}