#pragma once

namespace TyphoonEngine
{

	namespace Renderers
	{
	
		class RenderingContext;

		//
		// 3D renderer interface 
		//
		class IRenderer
		{

		public:

			//
			// Destructor
			//
			virtual ~IRenderer() = 0;

			//
			// Creates a platform-specific rendering context
			//
			RenderingContext* CreateContext() = 0;

			//
			// Returns the platform-agnostic rendering context
			//
			const RenderingContext* GetContext() const = 0;

			//
			// Returns the platform-agnostic rendering context
			//
			RenderingContext* GetContext() = 0;

		};
	}
}
