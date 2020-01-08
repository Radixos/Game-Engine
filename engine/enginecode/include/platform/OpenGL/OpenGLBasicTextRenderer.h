/**
\class OpenGLBasicTextRenderer.h
*/
#pragma once

#include "Rendering/Renderer.h"

namespace Engine {
	class OpenGLBasicTextRenderer : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override;	//!<Action a render command
		void beginScene(const SceneData& sceneData) override {};	//!<Prepare a scene
		void endScene() override {};	//!<End of scene
		void submit(const std::shared_ptr<Material>& material) override;	//!<Submit a material for drawing
		void flush() override {};	//!<Draw everything
	};
}