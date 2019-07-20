#include "TyphoonPCH.h"
#include "OpenGLVertexArray.h"
#include "Typhoon/Renderers/Buffer.h"

#include "glad/glad.h"

namespace TyphoonEngine
{
	namespace Renderers
	{
		// Type converter
		static GLenum ShaderDataTypeToOpenGLType( ShaderDataType type )
		{
			switch ( type )
			{
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:	return GL_INT;
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:	return GL_FLOAT;
			case ShaderDataType::Bool:	return GL_BOOL;
			}

			TE_ASSERT( false, "Unknown ShaderDataType!" );
			return 0;
		}

		OpenGLVertexArray::OpenGLVertexArray()
		{
			glCreateVertexArrays( 1, &m_bufferId );
		}
		
		OpenGLVertexArray::~OpenGLVertexArray()
		{
			glDeleteVertexArrays(1, &m_bufferId);
		}

		void OpenGLVertexArray::Bind() const
		{
			glBindVertexArray( m_bufferId );
		}

		void OpenGLVertexArray::Unbind() const
		{
			glBindVertexArray( 0 );
		}

		void OpenGLVertexArray::AddVertexBuffer( const std::shared_ptr<IVertexBuffer>& vBuffer ) 
		{
			glBindVertexArray( m_bufferId );
			vBuffer->Bind();

			TE_ASSERT(vBuffer->GetLayout().GetElements().size(), "Vertex buffer must have size > 0");
			
			glm::uint32 idx = 0;
			for ( const auto& element : vBuffer->GetLayout() )
			{
				glEnableVertexAttribArray( idx );
				glVertexAttribPointer( idx,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLType( element.m_type ),
					element.m_bNormalised ? GL_TRUE : GL_FALSE,
					vBuffer->GetLayout().GetStride(),
					(const void*)element.m_offset );
				++idx;
			}
			
			m_vertexBuffers.push_back( vBuffer );
		}
		
		void OpenGLVertexArray::SetIndexBuffer( const std::shared_ptr<IIndexBuffer>& iBuffer )
		{
			glBindVertexArray( m_bufferId );
			iBuffer->Bind();
			m_indexBuffer = iBuffer;
		}

	}
}