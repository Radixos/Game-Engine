/** /file ResourceManager.h
*/
#pragma once

#include "system.h"
#include "AssetManager.h"
#include <include\independent\Rendering\VertexArray.h>
#include <include\independent\Rendering\Shader.h>
#include <include\independent\Rendering\Texture.h>

namespace Engine
{
	class ResourceManager : public System
	{
	private:
		static AssetManager<IndexBuffer> m_indexBuffers;
		static AssetManager<Shader> m_shaders;
		static AssetManager<Texture> m_textures;
		static AssetManager<VertexArray> m_VAOs;
		static AssetManager<VertexBuffer> m_VBOs;
		static std::string parseFilePath(const std::string& str);	//!<Strip preceding dirs and file extension
	public:
		void start(SystemSignal init = SystemSignal::None, ...) {};	//!<Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) {};	//!<Stop the system - change this to free all resources

		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);
		static std::shared_ptr<Shader> addShader(const std::string& filepath);
		static std::shared_ptr<Texture> addTexture(const std::string& filepath);
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channel);	//or channels?
		static std::shared_ptr<VertexArray> addVAO(const std::string& name);
		static std::shared_ptr<VertexBuffer> addVBO(const std::string& name, float* vertices, unsigned int size, BufferLayout& layout);
	};
}