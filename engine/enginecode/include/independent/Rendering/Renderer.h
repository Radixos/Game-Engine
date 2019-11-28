#pragma once

//#include "engine_pch.h"

//Interface for rendering
namespace Engine
{
	class Renderer
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0;
		//virtual void beginScene(const SceneData& sceneData) = 0;
		virtual void endScene() = 0;
		//virtual void submit(const std::shared_ptr < Material & material) = 0;
		virtual void flush() = 0;

		static Renderer* createBasic3D();
	};
}