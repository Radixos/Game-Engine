/**
\class OpenGLVertexBuffer class
*/
#pragma once

#include "Rendering/Buffer.h"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size, BufferLayout& layout);	//!<Constructor for OpenGl VB
		~OpenGLVertexBuffer() override;	//!<Destructor

		void bind() const override;	//!<Bind OpenGL VB
		void unBind() const override;	//!<Unbind OpenGL VB
		void edit(float* vertices, unsigned int size, unsigned int offset) override {};	//!<Edit OpenGL VB
		const BufferLayout& GetLayout() const override { return m_Layout; };	//!<Function for returning the layout
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };	//!<Function for setting the layout
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};
}