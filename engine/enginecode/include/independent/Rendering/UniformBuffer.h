/**
/class UniformBuffer class
*/
#pragma once

#include <sstream>
#include "Shader.h"

namespace Engine {
	class UniformBuffer
	{
	protected:
	public:
		virtual void bind() = 0; //!<Bind the buffer
		virtual void unbind() = 0;	//!<Unbind the buffer
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) = 0;	//!<Bind shader block
		virtual void setData(unsigned int offset, unsigned int size, void* data) = 0;	//!<Set data in the buffer
		virtual UniformBufferLayout getLayout() const = 0;	//!<Get the layout of this buffer

		static UniformBuffer* create(unsigned int size, unsigned int layout);	//!<Returns an Rendering API specific UniformBuffer
		//static UniformBuffer* create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout);	//!<
	};
}