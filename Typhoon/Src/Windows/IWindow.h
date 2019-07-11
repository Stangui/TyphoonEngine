#pragma once

#include "Typhoon/Vector2.h"
#include "Events/Event.h"

namespace TyphoonEngine
{

	struct WindowProperties
	{
		Vec2i m_dimensions;
		bool m_vsync;
		std::string m_title;

		WindowProperties() :
			 m_dimensions(1270, 720)
			,m_vsync(true)
			,m_title("Typhoon Engine Window")
		{
		}
	};

	// Platform agnostic window
	class IWindow
	{
	
	public:

		using EventCallbackFn = std::function<void( Event& )>;

		virtual ~IWindow() {};
		
		inline virtual void SetEventCallback( const EventCallbackFn& callback ) = 0;
		
		virtual bool Update() = 0;
		virtual void SetVSync( bool bEnable ) = 0;
		virtual bool IsVSync( ) const = 0;
		virtual const Vec2i GetWindowSize() const = 0;

		static IWindow* Create( const WindowProperties& props = WindowProperties() );
	
	};
}