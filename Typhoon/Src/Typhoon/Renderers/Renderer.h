#pragma once

#include "RendererAPI.h"

namespace TyphoonEngine
{

	namespace Renderers
	{
	
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

			static void BeginScene();
			static void EndScene();
			static void Submit(const std::shared_ptr<VertexArray>& vArray);

		};
	}
}
