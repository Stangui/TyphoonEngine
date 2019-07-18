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
		class DirectXContext : public IRenderingContext
		{

		public:

			//
			// Constructor
			//
			DirectXContext();

			//
			// Destructor
			//
			virtual ~DirectXContext() override;

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