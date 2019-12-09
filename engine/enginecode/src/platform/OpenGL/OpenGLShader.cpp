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

	void OpenGLShader::uploadMat4(const std::string& name, glm::mat4* data)
	{
		//loc = glGetUniformLocation(m_TPShader->id(), "u_MVP");
		//glUniformMatrix4fv(loc, 1, GL_FALSE, &tpMVP[0][0]);
		GLuint loc = glGetUniformLocation(id(), name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, (GLfloat*)data);
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
}