/**file VertexArray.h 
*/
#include "engine_pch.h"
#include "Buffer.h"
namespace Engine {
	class VertexArray {
	public:
		virtual void bind() const = 0;	//!<Bind the vertex array object
		virtual void unbind() const = 0;	//!<Unbind vertex array object
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBeffer) = 0;	//!<Add a vertex buffer
		virtual void setindexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;	//!<Set the index buffer for all vertex buffer
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0;	//!<Get the vertex buffers
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;	//!<Get the index buffer
		virtual unsigned int getDrawCount() const = 0;	//!<Returns the number of triangles to draw

		static VertexArray * create();	//!<Return an API specific VertexArray
	};
}