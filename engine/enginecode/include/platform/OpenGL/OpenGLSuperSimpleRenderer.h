/** \file OpenGLSuperSimpleRenderer.h
*/

#pragma once

#include "engine_pch.h"
#include <sstream>
#include "Rendering/Renderer.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Material.h"

namespace Engine {
	class OpenGLSuperSimpleRenderer : public Renderer
	{
	private:
	public:
		//void actionCommand(RenderCommand* command) override;	//!<Action a render command
		//void beginScene(const SceneData& sceneData) {};	//!<Prepare a scene for submission
		void endScene() override {};	//!<End of scene
		//void submit(const std::shared_ptr<Material>& material) override;	//!<Submit a material for drawing
		void flush() override {};	//!<Draw everything
	};
}