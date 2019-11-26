/** /class OpenGLShader
*/
#pragma once

#include "Rendering/Shader.h"

namespace Engine {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);	//!<Constructor with path to all source code
		OpenGLShader(const std::string& vertexfilepath, const std::string& fragmentFilepath);	//!<Constructor with path to vertex and fragment
		inline unsigned int id() override { return m_OpenGL_ID; }	//!<Get the API id of the shader programme
		void bind() override;	//!<Bind the shader
		void unbind() override;	//!<Unbind the shader
		void uploadMat4(const std::string& name, glm::mat4* data) override;
		void uploadFloat3(const std::string& name, float a, float b, float c) override;
		void uploadFloat3(const std::string& name, float* data) override;
		void uploadInt(const std::string& name, int data) override;
	private:
		unsigned int m_OpenGL_ID;	//!<Shader ID
		void compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);	//!<Compile and link
	};
}