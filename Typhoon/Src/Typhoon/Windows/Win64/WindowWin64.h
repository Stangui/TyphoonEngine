#pragma once

#include "Typhoon/Windows/IWindow.h"
#include <GLFW/glfw3.h>

namespace TyphoonEngine
{

	class WindowWin64 : public IWindow
	{
	public:

		struct WindowData
		{
			Vec2i m_dims;
			uint8 m_monitorId;
			bool m_bVSync;
			WINDOW_TYPE m_type;

			EventCallbackFn m_callback;
		};

	public:

		WindowWin64( const WindowProperties& props );
		virtual ~WindowWin64() override;

		virtual void SetEventCallback( const EventCallbackFn& callback ) override;

		virtual bool Update() override;
		virtual void SetVSync( bool bEnable ) override;
		virtual bool IsVSync() const override;
		virtual const Vec2i GetWindowSize() const override;
		virtual void* GetNativeWindow() const override;

	private:

		Vec2i _calculateWindowPos( GLFWmonitor* monitor, int sizeX, int sizeY );
		bool _init( const WindowProperties& props );
		void _setCallbacks(struct GLFWwindow* win = nullptr);
		void _shutdown();

		GLFWwindow* m_glWindow;
		WindowData m_windowData;

		static bool s_glfwInitialised;
	};
}
