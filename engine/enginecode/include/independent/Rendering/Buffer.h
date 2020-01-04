/** \class Buffer class
*/

#pragma once

#include "ShaderData.h"

namespace Engine {

	class BufferElement	//!<Buffer element class
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalised;

		BufferElement() {}	//!<Default constructor
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};	//!<Constructor


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

			ENG_CORE_INFO(false, "Unknown ShaderDataType!");
			return 0;
		}*/
	};

	class BufferLayout	//!<BufferLayout class
	{
	public:
		BufferLayout() {};	//!<Default constructor

		BufferLayout(const std::initializer_list<BufferElement>& elements)	//!<Constructor through which layout elements are passed
			: m_Elements(elements)
		{
			calcStrideAndOffsets();
		}
		 
		inline unsigned int GetStride() const { return m_Stride; }	//uint32_t=unsigned int ???
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }	//!<Vector iterator for begin
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }	//!<Vector iterator for end
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }	//!<Vector const iterator for begin
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }	//!<Vector const iterator for end
		
		void addElement(ShaderDataType datatype)	//!<addElement function 
		{
			m_Elements.push_back(BufferElement(datatype));
			calcStrideAndOffsets();
		}
	
	private:
		std::vector<BufferElement> m_Elements;	//!<Buffer elements
		unsigned int m_Stride = 0;	//!<Stride - distance between data lines
		
		void calcStrideAndOffsets()	//!<Calculate the stride distance and the offset for each element
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
			}
			m_Stride = offset;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////// TO CHECK

	class UniformBufferElement	//!<UniformBufferElement class
	{
	public:
		ShaderDataType m_dataType;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalised;

		UniformBufferElement() {}	//!<Default constructor
		UniformBufferElement(
			ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType), m_size(ShaderDataTypeSize(dataType)), m_offset(0), m_normalised(normalised) {};	//!<Constructor
	private:
		BufferLayout m_Layout;	//???
	};

	class UniformBufferLayout	//!<UniformBufferLayout class
	{
	public:
		UniformBufferLayout() {};	//!<Default constructor

		UniformBufferLayout(const std::initializer_list<UniformBufferElement>& elements)	//!<Constructor through which layout elements are passed
			: m_Elements(elements)
		{
			calcStrideAndOffsets();
		}

		inline unsigned int GetStride() const { return m_Stride; }	//uint32_t=unsigned int ???	//!<getStride function for returning stide
		inline const std::vector<UniformBufferElement>& GetElements() const { return m_Elements; }	//!<GetElements function for returning elements

		std::vector<UniformBufferElement>::iterator begin() { return m_Elements.begin(); }	//!<Vector iterator for begin
		std::vector<UniformBufferElement>::iterator end() { return m_Elements.end(); }	//!<Vector iterator for end
		std::vector<UniformBufferElement>::const_iterator begin() const { return m_Elements.begin(); }	//!<Vector const iterator for begin
		std::vector<UniformBufferElement>::const_iterator end() const { return m_Elements.end(); }	//!<Vector const iterator for end

		void addElement(ShaderDataType datatype)	//!<addElement function for adding elements
		{
			m_Elements.push_back(UniformBufferElement(datatype));
			calcStrideAndOffsets();
		}

	private:
		std::vector<UniformBufferElement> m_Elements;	// Buffer elements
		unsigned int m_Stride = 0;	// Stride - distance between data lines

		void calcStrideAndOffsets()	// Calculate the stride distance and the offset for each element
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
			}
			m_Stride = offset;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////// END TO CHECK

	class VertexBuffer	//!<VertexBuffer class
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;	//!<Virtual bind function
		virtual void unBind() const = 0;	//!<Virtual unBind function
		virtual void edit(float* vertices, unsigned int size, unsigned int offset) = 0;	//!<Virtual edit function
		virtual const BufferLayout& GetLayout() const = 0;	//!<Virtual GetLayout function
		virtual void SetLayout(const BufferLayout& layout) = 0;	//!<Virtual SetLayout function

		static VertexBuffer* create(float* vertices, unsigned int size, BufferLayout& layout);	//!<Static create function for VertexBuffer
	};

	class IndexBuffer	//!<IndexBuffer class
	{
	public:
		virtual ~IndexBuffer() = default;	//!<Virtual destructor

		virtual void bind() const = 0;	//!<Virtual bind function
		virtual void unBind() const = 0;	//!<Virtual unbind function

		virtual unsigned int GetCount() const = 0;	//!<Virtual GetCount function

		static IndexBuffer* create(unsigned int* indices, unsigned int size);	//!<Static create function for IndexBuffer
	};
}