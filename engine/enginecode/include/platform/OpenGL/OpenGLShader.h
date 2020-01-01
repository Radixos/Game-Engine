/** /class OpenGLShader
*/
#pragma once

#include "Rendering/Shader.h"
#include <map>

namespace Engine {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);	//!<Constructor with path to all source code
		OpenGLShader(const std::string& vertexfilepath, const std::string& fragmentFilepath);	//!<Constructor with path to vertex and fragment
		inline unsigned int id() override { return m_OpenGL_ID; }	//!<Get the API id of the shader programme
		void bind() override;	//!<Bind the shader
		void unbind() override;	//!<Unbind the shader
		void uploadMat4(const std::string& name, float* data) override;
		void uploadFloat3(const std::string& name, float a, float b, float c) override;
		void uploadFloat3(const std::string& name, float* data) override;
		void uploadInt(const std::string& name, int data) override;
		void uploadInt2(const std::string& name, int a, int b) override;
		void uploadBool(const std::string& name, bool data) override;
		void uploadVec2(const std::string& name, glm::vec2 data) override;
		void uploadVec3(const std::string& name, glm::vec3 data) override;
		//void uploadFloatVector4(const std::string& name, GLfloat* data) override;
		//void dispatchUniformUpload(ShaderDataType type, GLuint location, void* data) override;

		BufferLayout getBufferLayout() const override;	//!<Get the buffer layout for shader
	private:	//Change to protected?
		unsigned int m_OpenGL_ID;	//!<Shader ID
		void compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);	//!<Compile and link
	
		void uniformLayout(const std::string& path);	//!<Get uniform buffer layout path
		std::map<std::string, std::function<bool(void* data)>> m_dispatcher;	//!<Set map for uniform
	};
}