#include "TyphoonPCH.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//------------------------------------------------//
		OpenGLVertexBuffer::OpenGLVertexBuffer( const float* vertices, glm::uint32 size ) : m_bufferId( 0 )
		{
			glCreateBuffers( 1, &m_bufferId );
			glBindBuffer( GL_ARRAY_BUFFER, m_bufferId );
			glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
		}

		//------------------------------------------------//
		OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{
			glDeleteBuffers( 1, &m_bufferId );
		}

		//------------------------------------------------//
		void OpenGLVertexBuffer::Bind() const
		{
			glBindBuffer( GL_ARRAY_BUFFER, m_bufferId );
		}

		//------------------------------------------------//
		void OpenGLVertexBuffer::Unbind() const
		{
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
		}

		//------------------------------------------------//
		void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
		{
			m_layout = layout;
		}

		//------------------------------------------------//
		const BufferLayout& OpenGLVertexBuffer::GetLayout() const
		{
			return m_layout;
		}

		//------------------------------------------------//
		OpenGLIndexBuffer::OpenGLIndexBuffer( const glm::uint32* indices, glm::uint32 count ) : 
			m_bufferId(0)
			,m_count(count)
		{
			glCreateBuffers( 1, &m_bufferId );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_bufferId );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof(glm::uint32), indices, GL_STATIC_DRAW );
		}

		//------------------------------------------------//
		OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{
			glDeleteBuffers( 1, &m_bufferId );
		}

		//------------------------------------------------//
		void OpenGLIndexBuffer::Bind() const
		{
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_bufferId );
		}

		//------------------------------------------------//
		void OpenGLIndexBuffer::Unbind() const
		{
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		}

		//------------------------------------------------//
		const glm::uint32 OpenGLIndexBuffer::GetCount() const
		{
			return m_count;
		}

	}
}