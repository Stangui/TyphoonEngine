#pragma once

#include "Typhoon/Renderers/RenderingContext.h"

struct GLFWwindow;

namespace TyphoonEngine
{
	namespace Renderers
	{

		// 
		// Creates a platform-specific rendering context
		//
		class MetalContext : public IRenderingContext
		{

		public:

			//
			// Constructor
			// Parameters:
			//	win - GLFWwindow pointer
			//
			MetalContext();

			//
			// Destructor
			//
			virtual ~MetalContext() override;

			//
			// Creates context
			//
			void Init() override;

			//
			// Swaps rendering buffers
			//
			void SwapBuffers() override;

		};
	}
}