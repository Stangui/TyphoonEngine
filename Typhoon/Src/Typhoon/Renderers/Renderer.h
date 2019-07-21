#pragma once

#include "RendererAPI.h"

namespace TyphoonEngine
{

	namespace Renderers
	{
	
		class Camera;
		class Shader;

		///
		/// Struct to hold scene properties
		///
		struct SceneData
		{
			glm::mat4 m_viewProjMat;
		};

		/// 
		///  3D renderer interface 
		/// 
		class IRenderer
		{
		public:


		public:

			/// 
			///  Return current rendering API
			/// 
			inline static RendererAPI::API GetRenderAPI() { return RendererAPI::GetAPI(); }

			/// 
			///  Destructor
			/// 
			virtual ~IRenderer() {};

			static void BeginScene( const Camera& cam );
			static void EndScene();
			static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vArray, const glm::mat4& transform);

		private:

			static SceneData* m_sceneData;
		};
	}
}
