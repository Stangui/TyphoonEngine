#pragma once

#include "Typhoon/Vector2.h"
#include "Typhoon/Events/Event.h"

namespace TyphoonEngine
{

	enum class WINDOW_TYPE : uint8
	{
		BorderWindowed,
		BorderlessWindowed,
		FullscreenWindowed,
		Fullscreen
	};

	struct WindowProperties
	{
		Vec2i m_dimensions;
		bool m_bVSync : 1;
		WINDOW_TYPE m_type;
		uint8 m_monitorId;
		std::string m_title;

		WindowProperties() :
			 m_dimensions(1270, 720)
			, m_bVSync( true )
			, m_type( WINDOW_TYPE::BorderlessWindowed )
			, m_monitorId( 0 )
			, m_title("Typhoon Engine Application")
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
		virtual void* GetNativeWindow() const = 0;

		static IWindow* Create( const WindowProperties& props = WindowProperties() );
	
	};
}