/** /class Shader
	An interface class for creating API specific shader programmes
*/
#pragma once

//#include "glm/glm.hpp"
#include "Buffer.h"
#include <sstream>
#include <glm/glm.hpp>

namespace Engine {
	class Shader	//!<Shader class
	{
	public:
		virtual unsigned int id() = 0;	//!<Get the API id of the shader programme
		virtual void bind() = 0;	//!<Bind the shader
		virtual void unbind() = 0;	//!<Unbind the shader
		virtual void uploadMat4(const std::string& name, float* data) = 0;
		virtual void uploadFloat3(const std::string& name, float a, float b, float c) = 0;
		virtual void uploadFloat3(const std::string& name, float* data) = 0;
		virtual void uploadInt(const std::string& name, int data) = 0;
		virtual void uploadInt2(const std::string& name, int a, int b) = 0;
		virtual void uploadBool(const std::string& name, bool data) = 0;
		virtual void uploadVec2(const std::string& name, glm::vec2 data) = 0;
		virtual void uploadVec3(const std::string& name, glm::vec3 data) = 0;
		//virtual void uploadFloatVector4(const std::string& name, GLfloat* data) = 0;
		//virtual void dispatchUniformUpload(ShaderDataType type, GLuint location, void* data) = 0;

		virtual BufferLayout getBufferLayout() const = 0;	//!<Get the buffer layout for shader
		//virtual UniformLayout getUniformLayout() const = 0;	//!<Get the structure of the data which can be uploaded

		//virtual bool uploadData(const std::string& dataName, void* data) = 0;	//!<Virtual uploadData function

		static Shader* create(const std::string& filepath); //!<Create, compile and link API specific shader from single filepath
		static Shader* create(const std::string& vvertexfilepath, const std::string& fragmentFilepath);	//!<Create, compile and link API specific shader from vertex filepath and fragment filepath
	};
}