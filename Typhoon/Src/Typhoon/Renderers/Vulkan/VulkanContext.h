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
		class VulkanContext : public IRenderingContext
		{

		public:

			//
			// Constructor
			// Parameters:
			//	win - GLFWwindow pointer
			//
			VulkanContext( GLFWwindow* win );

			//
			// Destructor
			//
			virtual ~VulkanContext() override;

			//
			// Creates context
			//
			void Init() override;

			//
			// Swaps rendering buffers
			//
			void SwapBuffers() override;

		private:

			// Rendering window pointer
			GLFWwindow* m_window;
		};
	}
}