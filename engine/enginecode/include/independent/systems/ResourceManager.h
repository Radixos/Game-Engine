/**
/class ResourceManager class
*/
#pragma once

#include "system.h"
#include "AssetManager.h"
#include <include\independent\Rendering\VertexArray.h>
#include <include\independent\Rendering\Shader.h>
#include <include\independent\Rendering\Texture.h>
#include <include\independent\Rendering\UniformBuffer.h>
#include <include\platform\OpenGL\OpenGLMaterial.h>
#include <include\independent\Rendering\Character.h>
#include <unordered_map>

namespace Engine
{
	class ResourceManager : public System
	{
	private:
		static AssetManager<IndexBuffer> m_indexBuffers;	//!<Index buffers
		static AssetManager<Shader> m_shaders;	//!<Shaders
		static AssetManager<Texture> m_textures;	//!<Textures
		static AssetManager<VertexArray> m_VAOs;	//!<Vertex arrays
		static AssetManager<VertexBuffer> m_VBOs;	//!<Vertex buffers
		static AssetManager<UniformBuffer> m_UBOs;	//!<Uniform buffers
		static AssetManager<Material> m_materials;	//!<Materials
		static std::map<std::string, std::vector<Character>> m_characters;	//!<Renderable characters
		static const int m_ASCIIstart = 32;
		static const int m_ASCIIend = 126;
		static std::shared_ptr<Texture> m_fontTexture;	//!<Texture which stores fonts
		static std::string parseFilePath(const std::string& str);	//!<Strip preceding dirs and file extension
	public:
		void start(SystemSignal init = SystemSignal::None, ...) {};	//!<Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) {};	//!<Stop the system - change this to free all resources

		static std::shared_ptr<IndexBuffer> addIndexBuffer(const std::string& name, unsigned int* indices, unsigned int count);	//!<Add index buffer function
		static std::shared_ptr<Shader> addShader(const std::string& filepath);	//!<Add shader function
		static std::shared_ptr<Texture> addTexture(const std::string& filepath);	//!<Add texture function using filepath
		static std::shared_ptr<Texture> addTexture(const std::string& name, unsigned int width, unsigned int height, unsigned int channel);	//or channels?	//!<Add texture function using parameters
		static std::shared_ptr<VertexArray> addVAO(const std::string& name);	//!<Add VAO function
		static std::shared_ptr<VertexBuffer> addVBO(const std::string& name, float* vertices, unsigned int size, BufferLayout& layout);	//!<Add VBO function
		static std::shared_ptr<UniformBuffer> addUBO(const std::string& name, unsigned int size, UniformBufferLayout& layout);	//!<Add UBO function using layout
		static std::shared_ptr<UniformBuffer> addUBO(const std::string& name, unsigned int size, unsigned int rangeStart, unsigned int rangeEnd);	//!<Add UBO function using parameters
		//static std::shared_ptr<Material> addMaterial(const std::string& name, const std::shared_ptr<Shader& shader, const std::...);	//!<Add material function
		static void populateCharacters(std::unordered_map<std::string, unsigned int> fontsAndSizes);	//!<Populate characters function
		static std::shared_ptr<Character>getCharacter(std::string font, unsigned int ASCIIcode);	//!<Get character function
		inline static std::shared_ptr<Texture> getFontTexture() { return m_fontTexture; };	//!<Get font texture function
	};
}