/**
\class OpenGLVertexBuffer and OpenGLIndexBuffer classes
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

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);	//!<Constructor for OpenGl IB
		~OpenGLIndexBuffer() override;	//!<Destructor

		void bind() const override;	//!<Bind OpenGL IB
		void unBind() const override;	//!<Unbind OpenGL IB
		unsigned int GetCount() const override { return m_Count; };	//!<Function for returning the count
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}