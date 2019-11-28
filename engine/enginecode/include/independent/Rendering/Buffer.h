/** \file Buffer.h
*/

#pragma once

#include <glad\glad.h>

namespace Engine {
	
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Sampler2D
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		case ShaderDataType::Sampler2D:return 1;
		}

		//ENG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	static unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Sampler2D:	return 1;
		}
		return 0;
	}

	static ShaderDataType GLSLStrToSTD(const std::string& glslSrc)
	{
		ShaderDataType result = ShaderDataType::None;
		if (glslSrc == "bool") result = ShaderDataType::Bool;
		if (glslSrc == "int") result = ShaderDataType::Int;
		if (glslSrc == "ivec2") result = ShaderDataType::Int2;
		if (glslSrc == "ivec3") result = ShaderDataType::Int3;
		if (glslSrc == "ivec4") result = ShaderDataType::Int4;
		if (glslSrc == "float") result = ShaderDataType::Float;
		if (glslSrc == "vec2") result = ShaderDataType::Float2;
		if (glslSrc == "vec3") result = ShaderDataType::Float3;
		if (glslSrc == "vec4") result = ShaderDataType::Float4;
		if (glslSrc == "mat3") result = ShaderDataType::Mat3;
		if (glslSrc == "mat4") result = ShaderDataType::Mat4;
		if (glslSrc == "sampler2D") result = ShaderDataType::Sampler2D;

		return result;
	}

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		return 0;
	}

	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalised;

		BufferElement() {};
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};


		/*std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}*/
	};

	class BufferLayout
	{
	public:
		BufferLayout() {};	//!<Default constructor

		BufferLayout(const std::initializer_list<BufferElement>& elements)	//!<Constructor through which layout elements are passed
			: m_Elements(elements)
		{
			calcStrideAndOffsets();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		void addElement(ShaderDataType datatype)
		{
			m_Elements.push_back(BufferElement(datatype));
			calcStrideAndOffsets();
		}
	private:
		void calcStrideAndOffsets()	// Calculate the stride distance and the offset for each element
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
				m_Stride += element.m_size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;	// Buffer elements
		unsigned int m_Stride = 0;	// Stride - distance between data lines
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void edit(float* vertices, unsigned int size, unsigned int offset) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		//virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* create(float* vertices, unsigned int size, BufferLayout& layout);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;

		static IndexBuffer* create(unsigned int* indices, unsigned int size);
	};
}