/**
\class OpenGLIndexBuffer class
*/

#pragma once

#include "Rendering/Buffer.h"

namespace Engine {
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