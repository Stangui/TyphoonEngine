#include "TyphoonPCH.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

namespace TyphoonEngine
{
	namespace Renderers
	{

		SceneData* IRenderer::m_sceneData = new SceneData;

		void IRenderer::RenderFrame(const Camera& cam) 
		{
			_BeginScene(cam);

			for ( const RenderablePtr& obj : m_sceneData->m_objects )
			{
				_Submit( obj );
			}
			_EndScene();
		}

		void IRenderer::_BeginScene( const Camera& cam )
		{
			m_sceneData->m_viewProjMat = cam.GetViewProjectionMatrix();
		}

		void IRenderer::_EndScene()
		{

		}

		void IRenderer::AddRenderObject( const RenderablePtr& renderable )
		{
			m_sceneData->m_objects.push_back( renderable );
		}

		void IRenderer::_Submit(const RenderablePtr& renderable)
		{
			if ( !renderable || !renderable->GetVertexArray() || !renderable->IsEnabled() )
			{
				return;
			}

			if ( renderable->GetShader() )
			{
				renderable->GetShader()->Bind();
				renderable->GetShader()->UploadUniformMat4( "u_vpMat", m_sceneData->m_viewProjMat );
				renderable->GetShader()->UploadUniformMat4( "u_transform", renderable->GetTransform() );
			}

			if ( renderable->GetVertexArray() )
			{
				renderable->GetVertexArray()->Bind();
				RenderCommand::DrawIndexed( renderable->GetVertexArray() );
			}
		}
	}
}