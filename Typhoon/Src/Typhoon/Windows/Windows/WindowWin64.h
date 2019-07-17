#pragma once

#include "Typhoon/Windows/IWindow.h"

#include "GLFW/glfw3.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace TyphoonEngine
{

	// Forward declrs
	namespace Renderers
	{
		class IRenderingContext;
	}

	//
	// Windows-specific application window
	//
	class WindowWin64 : public IWindow
	{
	public:

		//
		// Struct to pass window attributes to events
		//
		struct WindowData
		{
			glm::ivec2 m_dims;
			glm::uint8 m_monitorId;
			bool m_bVSync;
			WINDOW_TYPE m_type;

			EventCallbackFn m_callback;
		};

	public:
		
		//
		// Constuctor - creates win32 window
		// Paramaters:
		//	props - window properties 
		//
		WindowWin64( const WindowProperties& props );

		//
		// Destructor - destroys win32 window
		//
		virtual ~WindowWin64() override;

		//
		// Sets an event callback function
		// Parameters:
		//	callback - callback function pointer
		//
		virtual void SetEventCallback( const EventCallbackFn& callback ) override;

		//
		// Handles window updates
		//
		virtual bool Update() override;
		
		//
		// Sets window vsync
		// Parameters:
		//	bEnable - True/false
		//
		virtual void SetVSync( bool bEnable ) override;

		//
		// Returns whether vsync is enabled
		//
		virtual bool IsVSync() const override;

		//
		// Returns current window size
		//
		virtual const glm::ivec2 GetWindowSize() const override;

		//
		// Gets the native window pointer (GLFWwindow*)
		//
		virtual void* GetNativeWindow() const override;

	private:

		// 
		// Calculates where to position window based on monitor id and size
		// Parameters:
		//	monitor - monitor to display window on
		//	size - vector2d struct containing window width/height
		//
		glm::ivec2 _calculateWindowPos( GLFWmonitor* monitor, const glm::ivec2 size );

		//
		// Initialises/creates window
		//
		bool _init( const WindowProperties& props );

		//
		// Sets callbacks for several window events
		//
		void _setCallbacks(struct GLFWwindow* win = nullptr);

		//
		// Destroys window
		//
		void _shutdown();

		// Native window pointer
		GLFWwindow* m_glWindow;
		
		// Window event data
		WindowData m_windowData;

		// Rendering context
		Renderers::IRenderingContext* m_context;

		// Initialise GLFW once per application
		static bool s_glfwInitialised;
	};
}
