/**file VertexArray.h 
*/
#pragma once

#include "Buffer.h"
namespace Engine {
	class VertexArray {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBeffer) = 0;
		virtual void setindexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;
		virtual unsigned int getDrawCount() const = 0;

		static VertexArray * create();
	};
}