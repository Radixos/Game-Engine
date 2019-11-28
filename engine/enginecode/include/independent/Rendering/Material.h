/** \file Material.h
*/
#pragma once

#include "engine_pch.h"
#include <sstream>
#include <variant>
#include <map>
#include "Shader.h"
#include "VertexArray.h"

namespace Engine {
	class Material
	{
	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0;	//!<Set the shader
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0;	//!<Set the geometry using variant
		virtual void setDataBlock(const std::map<std::string, void*>& data) = 0;	//!<Set a block of data as the per draw data
		virtual void setDataElement(const std::string& dataName, void* data) = 0;	//!<Set a single uniform
		virtual void setVertexData(float* vertices, unsigned int size, unsigned int offset) = 0;	//!<Set the geometry directly

		virtual std::shared_ptr<Shader> getShader() = 0;	//!<Get the shader
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0;	//!<Get the geometry
		virtual std::map<std::string, void*> getData() = 0;	//!<Get the per draw data

		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> & VAO);	//!<Create VAO
		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer> & VBO);	//!<Create VBO
	};
}