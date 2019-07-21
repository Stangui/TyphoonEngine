#include "TyphoonPCH.h"
#include "Renderable.h"

#include "VertexArray.h"
#include "Shader.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		//-------------------------------------------//
		Renderable::Renderable( std::shared_ptr<VertexArray>& vArray, std::shared_ptr<Shader>& shader, glm::uint8 renderqueue ) :
			  m_vertexArray( vArray )
			, m_shader( shader )
			, m_transform( glm::mat4( 1.f ) )
			, m_renderQueue( renderqueue )
			, m_bEnabled( true )
		{
		}

		//-------------------------------------------//
		Renderable::~Renderable()
		{
		}

		//-------------------------------------------//
		const std::shared_ptr<Shader>& Renderable::GetShader() const
		{
			return m_shader;
		}
		
		//-------------------------------------------//
		const std::shared_ptr<VertexArray>& Renderable::GetVertexArray() const
		{
			return m_vertexArray;
		}

		//-------------------------------------------//
		void Renderable::SetTransform( const glm::mat4& transform )
		{
			m_transform = transform;
		}

		//-------------------------------------------//
		void Renderable::SetRenderqueue( const glm::uint8 renderqueue )
		{
			m_renderQueue = renderqueue;
		}

		//-------------------------------------------//
		const glm::mat4& Renderable::GetTransform() const
		{
			return m_transform;
		}

		//-------------------------------------------//
		void Renderable::SetEnabled( bool bEnable )
		{
			m_bEnabled = bEnable;
		}

		//-------------------------------------------//
		const bool Renderable::IsEnabled() const
		{
			return m_bEnabled;
		}

	}
}
