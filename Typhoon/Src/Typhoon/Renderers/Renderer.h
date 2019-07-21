#pragma once

#include "RendererAPI.h"
#include "Renderable.h"

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
			RenderVec m_objects;
		};

		/// 
		///  3D renderer interface 
		/// 
		class IRenderer
		{

		public:

			/// 
			///  Return current rendering API
			/// 
			inline static RendererAPI::API GetRenderAPI() { return RendererAPI::GetAPI(); }

			/// 
			///  Destructor
			/// 
			virtual ~IRenderer() {};

			///
			/// Render a single frame
			///
			void RenderFrame( const Camera& cam );

			///
			/// Adds a RenderObject to the render list
			///
			void AddRenderObject( const RenderablePtr& obj );

		private:

			void _BeginScene( const Camera& cam );
			void _EndScene();
			void _Submit( const RenderablePtr& renderable );

			static SceneData* m_sceneData;
		};
	}
}
