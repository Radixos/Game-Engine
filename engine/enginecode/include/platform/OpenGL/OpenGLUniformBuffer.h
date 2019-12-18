#pragma once

#include "Rendering/UniformBuffer.h"

namespace Engine {
	class OpenGLUniformBuffer : public UniformBuffer
	{
	protected:
		UniformBufferLayout m_Layout;
		unsigned int m_uniformBuffer;
		unsigned int m_bindingPoint;
	public:
		//OpenGLUniformBuffer(unsigned int id, unsigned int size);
		void bind() override; //!<Bind the buffer
		void unbind() override;	//!<Unbind the buffer
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const std::string& blockName) override;	//!<Bind shader block
		void setData(unsigned int offset, unsigned int size, void* data) override;	//!<Set data in the buffer
		UniformBufferLayout getLayout() const override { return m_Layout; };	//!<Get the layout of this buffer

		static UniformBuffer* create(unsigned int size, UniformBufferLayout& layout);	//!<Returns an Rendering API specific UniformBuffer
		//static UniformBuffer* create(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout);	//!<
	};
}