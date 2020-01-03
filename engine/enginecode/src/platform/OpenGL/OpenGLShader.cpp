/** \file OpenGLShader.cpp
*/

#include "engine_pch.h"

#include "include/platform/OpenGL/OpenGLShader.h"
#include "systems/Log.h"
#include <fstream>
#include <glad\glad.h>

namespace Engine {
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX = 0, FRAGMENT } region;
		if (!handle.is_open()) ENG_CORE_WARN("Could not open shader file '{0}'.", filepath);

		std::string line, src[2];
		while (getline(handle, line))
		{
			//Determine shader src type
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geometry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (region != NONE) src[region] += (line + "\n");
		}

		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);

		bind();
	}

	OpenGLShader::OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	{
		std::fstream handle;
		enum { VERTEX = 0, FRAGMENT } region;
		std::string line, src[2];

		handle.open(vertexFilepath, std::ios::in);
		if (!handle.is_open()) ENG_CORE_WARN("Could not open shader file '{0}'.", vertexFilepath);

		while (getline(handle, line))
		{
			src[VERTEX] += line;
		}
		handle.close();

		handle.open(fragmentFilepath, std::ios::in);
		if (handle.is_open()) ENG_CORE_WARN("Could not open shader file '{0}',", fragmentFilepath);

		while (getline(handle, line))
		{
			src[FRAGMENT] += line;
		}
		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);

		bind();
	}

	void OpenGLShader::bind()
	{
		glUseProgram(m_OpenGL_ID);
	}

	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		//Compile Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* src = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &src, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			std::string errorString(infoLog.begin(), infoLog.end());

			ENG_CORE_WARN("Vertex shader compile failure:\n {0}", errorString);

			glDeleteShader(vertexShader);
			return;
		}

		//Compile fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		src = fragmentShaderSrc.c_str();

		glShaderSource(fragmentShader, 1, &src, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			std::string errorString(infoLog.begin(), infoLog.end());

			ENG_CORE_WARN("Fragment shader compile failure:\n {0}", errorString);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		//Link shaders
		m_OpenGL_ID = glCreateProgram();
		glAttachShader(m_OpenGL_ID, vertexShader);
		glAttachShader(m_OpenGL_ID, fragmentShader);
		glLinkProgram(m_OpenGL_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]);

			std::string errorString(infoLog.begin(), infoLog.end());
			ENG_CORE_WARN("Shader linker failure:\n {0}", errorString);

			glDeleteProgram(m_OpenGL_ID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		glDetachShader(m_OpenGL_ID, vertexShader);
		glDetachShader(m_OpenGL_ID, fragmentShader);
	}

	void OpenGLShader::uploadMat4(const std::string& name, float* data)
	{
		//loc = glGetUniformLocation(m_TPShader->id(), "u_MVP");
		//glUniformMatrix4fv(loc, 1, GL_FALSE, &tpMVP[0][0]);
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, data);
	}

	void OpenGLShader::uploadFloat3(const std::string& name, float a, float b, float c)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform3f(loc, a, b, c);
	}

	void OpenGLShader::uploadFloat3(const std::string& name, float* data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform3fv(loc, 1, data);
	}

	void OpenGLShader::uploadInt(const std::string& name, int data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform1i(loc, data);
	}

	void OpenGLShader::uploadInt2(const std::string& name, int a, int b)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform2i(loc, a, b);
	}

	void OpenGLShader::uploadBool(const std::string& name, bool data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform1i(loc, data);
	}

	void OpenGLShader::uploadVec2(const std::string& name, glm::vec2 data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		// To finish
	}

	void OpenGLShader::uploadVec3(const std::string& name, glm::vec3 data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		// To finish
	}

	/*void OpenGLShader::uploadFloatVector4(const std::string& name, GLfloat* data)
	{
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniform4fv(loc, 1, data);
	}*/

	void OpenGLShader::uniformLayout(const std::string& path)
	{
		std::fstream readPath(path, std::ios::in);

		if (readPath.is_open() == false)
		{
			ENG_CORE_ERROR("Could not open {0}", path);
		}

		std::string line;	//line
		std::string uniform;	//uniform
		std::string type;	//type
		std::string name;	//name

		while (getline(readPath, line))
		{
			if (line.find("uniform") != std::string::npos)
			{
				std::stringstream stringStream(line);
				stringStream >> uniform;
				stringStream >> type;
				stringStream >> name;

				if (name.at(name.length() - 1) == ';')
				{
					name.pop_back();
				}

				unsigned int loc = glGetUniformLocation(m_OpenGL_ID, name.c_str());	//location

				m_uniform[name] = std::pair<ShaderDataType, unsigned int>(GLSLStrToSTD(type), loc);

				switch (GLSLStrToSTD(type))	//ShaderDataType::StringToDataType
				{
				case ShaderDataType::None:
					m_dispatcher[name] = [](void* data)
					{
						return false;
					};
					break;
				case ShaderDataType::Int:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform1i(loc, (GLint)data);
						return true;
					};
					break;
				case ShaderDataType::Int2:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform2iv(loc, 1, (GLint*)data);
						return true;
					};
					break;
				case ShaderDataType::Int3:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform3iv(loc, 1, (GLint*)data);
						return true;
					};
					break;
				case ShaderDataType::Int4:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform4iv(loc, 1, (GLint*)data);
						return true;
					};
					break;
				case ShaderDataType::Mat3:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniformMatrix3fv(loc, 1, GL_FALSE, (GLfloat*)data);
						return true;
					};
					break;
				case ShaderDataType::Mat4:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat*)data);
						return true;
					};
					break;
				//case ShaderDataType::Float:
				//	m_dispatcher[name] = [loc](void* data)
				//	{
				//		glUniform1f(loc, /*???*/);
				//		return true;
				//	};
				//	break;
				//case ShaderDataType::Float2:
				//	m_dispatcher[name] = [loc](void* data)
				//	{
				//		glUniform2f(loc, /*???*/);
				//		return true;
				//	};
				//	break;
				//case ShaderDataType::Float3:
				//	m_dispatcher[name] = [loc](void* data)
				//	{
				//		glUniform3f(loc, /*???*/);
				//		return true;
				//	};
				//	break;
				case ShaderDataType::Float:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform1fv(loc, 1, (GLfloat*)data);
						return true;
					};
					break;
				case ShaderDataType::Float2:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform2fv(loc, 1, (GLfloat*)data);
						return true;
					};
					break;
				case ShaderDataType::Float3:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform3fv(loc, 1, (GLfloat*)data);
						return true;
					};
					break;
				case ShaderDataType::Float4:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform4fv(loc, 1, (GLfloat*)data);
						return true;
					};
					break;
				case ShaderDataType::Sampler2D:
					/*m_dispatcher[name] = [loc](void* data)
					{
						glUniform4fv(loc, 1, (GLfloat*)data);
						return true;
					};*/
					break;
				case ShaderDataType::Bool:
					m_dispatcher[name] = [loc](void* data)
					{
						glUniform4fv(loc, 1, (GLfloat*)data);
						return true;
					};
					break;
				}
			}
		}
	}

	bool OpenGLShader::uploadData(const std::string& dataName, void* data)
	{
		return m_dispatcher[dataName](data);
	}

	BufferLayout OpenGLShader::getBufferLayout() const
	{
		return BufferLayout();
	}

	std::map<std::string, std::pair<ShaderDataType, unsigned int>> OpenGLShader::getUniform()
	{
		return m_uniform;
	}

	/*void OpenGLShader::dispatchUniformUpload(ShaderDataType type, GLuint location, void* data)
	{
		const float* addrf;
		const int* addri;
		GLfloat valueFloat;
		GLint valueInt;

		switch (type)
		{
		case ShaderDataType::Bool:
			valueInt = *(bool*)data;
			glUniform1i(location, valueInt);
			break;
		case ShaderDataType::Int:
			valueInt = *(int*)data;
			glUniform1i(location, valueInt);
			break;
		case ShaderDataType::Int2:
			valueInt = *(const int*)data;
			glUniform2iv(location, 1, addri);
			break;

			//To finish???
		}
	}*/
}