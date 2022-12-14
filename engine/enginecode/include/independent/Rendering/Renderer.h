/**
\class Renderer class
*/

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
	using SceneData = std::unordered_map<std::shared_ptr<UniformBufferElement>, std::vector<void*>>;	//!<Unordered map for SceneData
	using PerDrawData = std::map<std::string, void*>;	//!<Map for PerDrawData

	//Interface for rendering
	class Renderer	//!<Renderer class
	{
	public:
		virtual void actionCommand(RenderCommand* command) = 0;	//!<Action a render command
		virtual void beginScene(const SceneData& sceneData) = 0;	//!<Prepare a scene for submission
		virtual void endScene() = 0;	//!<End of scene
		virtual void submit(const std::shared_ptr<Material>& material) = 0;	//!<Submit a material for drawing
		virtual void flush() = 0;	//!<Draw everything

		static Renderer* createBasic3D();	//!<Static function to create basic3D
		static Renderer* createBasicTextRenderer2D();	//!<Static function to create basic text renderer2D
	};
}