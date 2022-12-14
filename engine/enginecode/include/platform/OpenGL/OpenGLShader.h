/**
/class OpenGLShader class
*/
#pragma once

#include "Rendering/Shader.h"
#include <map>
#include <functional>

namespace Engine {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);	//!<Constructor with path to all source code
		OpenGLShader(const std::string& vertexfilepath, const std::string& fragmentFilepath);	//!<Constructor with path to vertex and fragment
		inline unsigned int id() override { return m_OpenGL_ID; }	//!<Get the API id of the shader programme
		void bind() override;	//!<Bind the shader
		void unbind() override;	//!<Unbind the shader

		bool uploadData(const std::string& dataName, void* data) override;

		BufferLayout getBufferLayout() const override;	//!<Get the buffer layout for shader
		std::map<std::string, std::pair<ShaderDataType, unsigned int>> getUniform();
	private:	//Change to protected?
		unsigned int m_OpenGL_ID;	//!<Shader ID
		void compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);	//!<Compile and link
	
		void uniformLayout(const std::string& path);	//!<Get uniform buffer layout path
		std::map<std::string, std::function<bool(void* data)>> m_dispatcher;	//!<Set map for uniform
	};
}