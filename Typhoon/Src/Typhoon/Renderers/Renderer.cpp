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

		void IRenderer::BeginScene( const Camera& cam )
		{
			m_sceneData->m_viewProjMat = cam.GetViewProjectionMatrix();
		}

		void IRenderer::EndScene()
		{

		}

		void IRenderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vArray, const glm::mat4& transform)
		{
			shader->Bind();
			shader->UploadUniformMat4( "u_vpMat", m_sceneData->m_viewProjMat );
			shader->UploadUniformMat4( "u_transform", transform );
			
			vArray->Bind();

			RenderCommand::DrawIndexed(vArray);
		}
	}
}