/**
/class VertexArray class
*/
#pragma once

#include "Buffer.h"

namespace Engine {
	class VertexArray
	{
	public:
		virtual void bind() const = 0;	//!<Virtual function for binding the vertex array
		virtual void unbind() const = 0;	//!<Virtual function for unbinding the vertex array
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBeffer) = 0;	//!<Virtual function for setting the vertex buffer
		virtual void setindexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;	//!<Virtual function for setting the index buffer
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;	//!<Virtual function for getting the vertex buffer
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;	//!<Virtual function for getting the index buffer
		virtual unsigned int getDrawCount() const = 0;	//!<Virtual function for getting the draw count

		static VertexArray * create();	//!<Create function
	};
}