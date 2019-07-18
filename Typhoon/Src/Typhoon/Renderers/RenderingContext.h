#pragma once

namespace TyphoonEngine
{

	namespace Renderers
	{
	
		//
		// Rendering context interface
		//
		class IRenderingContext
		{

		public:

			//
			// Destructor
			//
			virtual ~IRenderingContext() {};

			// 
			// Initialise platform-specific rendering context
			//
			virtual void Init() = 0;

			// 
			// Swap platform-specific buffers
			//
			virtual void SwapBuffers() = 0;

		};
	}
}