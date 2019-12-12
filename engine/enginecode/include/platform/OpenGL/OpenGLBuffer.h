#pragma once

#include "Rendering/Buffer.h"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size, BufferLayout& layout);
		~OpenGLVertexBuffer() override;

		void bind() const override;
		void unBind() const override;
		void edit(float* vertices, unsigned int size, unsigned int offset) override {};
		const BufferLayout& GetLayout() const override { return m_Layout; };
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int size);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unBind() const override;
		unsigned int GetCount() const override { return m_Count; };
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}