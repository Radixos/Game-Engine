#pragma once

#include "include/independent/rendering/VertexArray.h"
#include "include/independent/rendering/Buffer.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		unsigned int m_id;
	public:
		OpenGLVertexArray();
		void bind() const override;
		void unbind() const override;
		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBeffer) override;
		void setindexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		std::shared_ptr<VertexBuffer> getVertexBuffer() const override { return m_vertexBuffer; };
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return m_indexBuffer; };
		unsigned int getDrawCount() const override { return m_indexBuffer->GetCount(); }
	};
}