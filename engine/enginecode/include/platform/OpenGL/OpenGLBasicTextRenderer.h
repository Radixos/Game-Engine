#pragma once
/** \file OpenGLBasicRenderer.h
*/
#pragma once

#include "Rendering/Renderer.h"

namespace Engine {
	class OpenGLBasicTextRenderer : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override;
		void beginScene(const SceneData& sceneData) override {};
		void endScene() override {};
		void submit(const std::shared_ptr<Material>& material) override;
		void flush() override {};
	};
}