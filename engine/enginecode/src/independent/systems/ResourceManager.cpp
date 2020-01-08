#include "engine_pch.h"

#include "systems/AssetManager.h"
#include "systems/ResourceManager.h"

namespace Engine {

	
	AssetManager<IndexBuffer> ResourceManager::m_indexBuffers;
	AssetManager<Shader> ResourceManager::m_shaders;
	AssetManager<Texture> ResourceManager::m_textures;
	AssetManager<VertexArray> ResourceManager::m_VAOs;
	AssetManager<VertexBuffer> ResourceManager::m_VBOs;
	AssetManager<UniformBuffer> ResourceManager::m_UBOs;
	AssetManager<Material> ResourceManager::m_materials;
	std::shared_ptr<Texture> ResourceManager::m_fontTexture;

	std::shared_ptr<IndexBuffer> ResourceManager::addIndexBuffer(const std::string & name, unsigned int * indices, unsigned int count)
	{
		std::shared_ptr<IndexBuffer> indexBuffers;
		indexBuffers.reset(Engine::IndexBuffer::create(indices, sizeof(indices)));
		m_indexBuffers.add(name, indexBuffers);
		return indexBuffers;
	}

	std::shared_ptr<Shader> ResourceManager::addShader(const std::string &name, const std::string & filepath)
	{
		std::shared_ptr<Shader> shader;
		shader.reset(Engine::Shader::create(filepath));
		m_shaders.add(name, shader);
		return shader;
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string &name, const std::string & filepath)
	{
		std::shared_ptr<Texture> textures;
		textures.reset(Engine::Texture::createFromFile(filepath));
		m_textures.add(name, textures);
		return textures;
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const std::string & name, unsigned int width, unsigned int height, unsigned int channel)
	{
		//std::shared_ptr<Texture> 
		return std::shared_ptr<Texture>();
	}

	std::shared_ptr<VertexArray> ResourceManager::addVAO(const std::string & name)
	{
		std::shared_ptr<VertexArray> VAO;
		VAO.reset(Engine::VertexArray::create());
		m_VAOs.add(name, VAO);
		return VAO;
	}

	std::shared_ptr<VertexBuffer> ResourceManager::addVBO(const std::string & name, float * vertices, unsigned int size, BufferLayout & layout)
	{
		//std::shared_ptr<VertexBuffer> VBO;
		//VBO.reset(Engine::VertexBuffer::create());
		return std::shared_ptr<VertexBuffer>();
	}

	std::shared_ptr<UniformBuffer> ResourceManager::addUBO(const std::string & name, unsigned int size, UniformBufferLayout & layout)
	{
		return std::shared_ptr<UniformBuffer>();
	}

	std::shared_ptr<UniformBuffer> ResourceManager::addUBO(const std::string & name, unsigned int size, unsigned int rangeStart, unsigned int rangeEnd)
	{
		return std::shared_ptr<UniformBuffer>();
	}

	void ResourceManager::populateCharacters(std::unordered_map<std::string, unsigned int> fontsAndSizes)
	{

	}

	std::shared_ptr<Character> ResourceManager::getCharacter(std::string font, unsigned int ASCIIcode)
	{
		return std::shared_ptr<Character>();
	}
}