#pragma once

#include "glm/glm.hpp"
#include "Typhoon/Core.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//
		// Enumeration for shader data types
		//
		enum class ShaderDataType
		{
			None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
		};

		//
		// Get byte size for ShaderDataType
		//
		static glm::uint32 ShaderDataTypeSize( ShaderDataType type )
		{
			switch ( type )
			{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
			}

			TE_ASSERT( false, "Unknown ShaderDataType!" );
			return 0;
		}

		//
		// Shader buffer element definition
		//
		struct BufferElement
		{
			std::string m_name;
			ShaderDataType m_type;
			glm::uint32 m_offset;
			glm::uint32 m_size;
			bool m_bNormalised;

			BufferElement() {}

			BufferElement( ShaderDataType type, const std::string& name, bool normalised = false ) :
				m_name( name )
				, m_type( type )
				, m_size( ShaderDataTypeSize( type ) )
				, m_offset( 0 )
				, m_bNormalised( normalised )
			{
			}

			glm::uint32 GetComponentCount() const
			{
				switch ( m_type )
				{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Mat3:		return 9;
				case ShaderDataType::Mat4:		return 16;
				case ShaderDataType::Bool:		return 1;
				}
				
				TE_ASSERT( false, "Unknown ShaderDataType!" );
				return 0;
			}
		};

		//
		// Layout description for a single shader buffer
		//
		class BufferLayout
		{

		public:

			typedef std::vector<BufferElement> ElementVec;

		public:

			//
			// Default constructor
			//
			BufferLayout() {}

			//
			// Initializer list constructor
			// 
			BufferLayout( const std::initializer_list<BufferElement>& elements ) : m_elements(elements)
			{
				CalculateOffsetAndStride();
			}

			//
			// Gets stride of this layout
			// Returns:
			//	stride of this layout in bytes.
			//
			const glm::uint32 GetStride() const
			{
				return m_stride;
			}

			//
			// Returns element vector
			//
			const ElementVec& GetElements() const { return m_elements; }

			// Range-For iterators
			ElementVec::iterator begin() { return m_elements.begin(); }
			ElementVec::iterator end() { return m_elements.end(); }

			// Const Range-For iterators
			ElementVec::const_iterator begin() const { return m_elements.begin(); }
			ElementVec::const_iterator end() const { return m_elements.end(); }

		private:

			//
			// Calculates byte stride/offset for this layout
			//
			void CalculateOffsetAndStride()
			{
				glm::uint32 offset = 0;
				m_stride = 0;

				for ( auto& e : m_elements )
				{
					e.m_offset = offset;
					offset += e.m_size;
					m_stride += e.m_size;
				}
			}

			// Vector of buffer elements
			std::vector<BufferElement> m_elements;
			
			// Size of stride in bytes
			glm::uint32 m_stride;
		};

		//
		// Generic vertex buffer class
		//
		class IVertexBuffer
		{

		public:

			virtual ~IVertexBuffer() {};

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual void SetLayout( const BufferLayout& layout ) = 0;
			virtual const BufferLayout& GetLayout() const = 0;

			static IVertexBuffer* Create( const float* vertices, glm::uint32 size );
		};

		//
		// Generic index buffer class
		//
		class IIndexBuffer
		{

		public:

			virtual ~IIndexBuffer() {};

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual const glm::uint32 GetCount() const = 0;

			static IIndexBuffer* Create( const glm::uint32* indices, glm::uint32 count );
		};

	}
}