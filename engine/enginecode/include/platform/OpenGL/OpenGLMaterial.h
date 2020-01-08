/**
\class OpenGLMaterial class
*/
#pragma once

#include "include/independent/Rendering/Material.h"
namespace Engine {
	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);	//!<Constructor
		//OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO);	//!<Constructor

		void init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);	//!<Initialise the material
		void setShader(const std::shared_ptr<Shader>& shader) override;	//!<Set the shader
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;	//!<Set the geometry using variant
		void setDataBlock(const std::map<std::string, void*>& data) override;	//!<Set a block of data as the per draw data
		void setDataElement(const std::string& dataName, void* data) override;	//!<Set a single uniform
		void setVertexData(float* vertices, unsigned int size, unsigned int offset) override;	//!<Set the geometry directly
		inline std::shared_ptr<Shader> getShader() override { return m_shader; }	//!<Get the shader
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override
			{ return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geometry); }	//!<Get the geometry
		inline std::map<std::string, void*> getData() override { return m_data; }	//!<Get the per draw data
	private:
		std::shared_ptr<Shader> m_shader;	//!<The shader
		std::shared_ptr<VertexArray> m_geometry;	//!<The geometry
		std::map<std::string, void*> m_data;	//!<The data
	};
}