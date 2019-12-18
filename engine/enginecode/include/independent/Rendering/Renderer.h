#pragma once
#include <unordered_map>
#include <include\independent\Rendering\RenderCommand.h>
#include <memory>
#include <map>
#include <include\independent\Rendering\Material.h>

//#include "engine_pch.h"

//Interface for rendering
namespace Engine
{
	using SceneData = std::unordered_map<std::shared_ptr<UniformBufferElement>, std::vector<void*>>;
	using PerDrawData = std::map<std::string, void*>;

	//Interface for rendering
	class Renderer
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0;	//!<Action a render command
		virtual void beginScene(const SceneData& sceneData) = 0;	//!<Prepare a scene for submission
		virtual void endScene() = 0;	//!<End of scene
		virtual void submit(const std::shared_ptr<Material>& material) = 0;	//!<Submit a material for drawing
		virtual void flush() = 0;	//!<Draw everything

		static Renderer* createBasic3D();
		static Renderer* createBasicTextRenderer2D();
	};
}