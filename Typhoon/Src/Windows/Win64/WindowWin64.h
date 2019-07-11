#pragma once

#include "Windows/IWindow.h"
#include <GLFW/glfw3.h>

namespace TyphoonEngine
{

	class WindowWin64 : public IWindow
	{
	public:

		struct WindowData
		{
			Vec2i m_dims;
			bool m_vSync;
			EventCallbackFn m_callback;
		};

	public:

		WindowWin64( const WindowProperties& props );
		virtual ~WindowWin64() override;

		virtual void SetEventCallback( const EventCallbackFn& callback ) override;

		virtual bool Update() override;
		virtual void SetVSync( bool bEnable ) override;
		virtual bool IsVSync() const override;
		virtual const Vec2i GetWindowSize() const;

	private:

		bool init( const WindowProperties& props );
		void shutdown();

		GLFWwindow* m_glWindow;
		WindowData m_windowData;

		static bool s_glfwInitialised;
	};
}
