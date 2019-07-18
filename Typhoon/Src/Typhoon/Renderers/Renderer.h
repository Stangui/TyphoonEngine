#pragma once

namespace TyphoonEngine
{

	namespace Renderers
	{
	
		//
		// Rendering API enum
		//
		enum class RenderAPI : unsigned char
		{
			None = 0, OpenGL, DirectX, Vulkan, Metal
		};

		class RenderingContext;

		//
		// 3D renderer interface 
		//
		class IRenderer
		{

		public:

			//
			// Return current rendering API
			//
			static inline const RenderAPI GetRenderAPI() { return s_renderAPI; }

			//
			// Return current rendering API
			//
			static inline void SetRenderAPI( RenderAPI api ) { s_renderAPI = api; }

			//
			// Destructor
			//
			virtual ~IRenderer() = 0;

			//
			// Creates a platform-specific rendering context
			//
			virtual RenderingContext* CreateContext() = 0;

			//
			// Returns the platform-agnostic rendering context
			//
			virtual const RenderingContext* GetContext() const = 0;

			//
			// Returns the platform-agnostic rendering context
			//
			virtual RenderingContext* GetContext() = 0;

		private:

			// Rendering API type
			static RenderAPI s_renderAPI;

		};
	}
}
