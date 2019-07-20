#pragma once

#include "Typhoon/Events/Event.h"

namespace TyphoonEngine
{

	/// 
	///  Type of window to create
	/// 
	enum class EWINDOW_TYPE : glm::uint8
	{
		BorderWindowed,
		BorderlessWindowed,
		FullscreenWindowed,
		Fullscreen
	};

	/// 
	///  Properties of window to create
	/// 
	struct WindowProperties
	{
		glm::ivec2 m_dimensions;	///  size
		bool m_bVSync : 1;			///  vsync enabled
		EWINDOW_TYPE m_type;		///  window style
		glm::uint8 m_monitorId;		///  monitor to display
		std::string m_title;		///  window title text

		WindowProperties() :
			 m_dimensions(1270, 720)
			, m_bVSync( true )
			, m_type( EWINDOW_TYPE::BorderlessWindowed )
			, m_monitorId( 0 )
			, m_title("Typhoon Application")
		{
		}
	};

	/// 
	///  Platform agnostic window
	/// 
	class IWindow
	{
	
	public:

		/// 
		///  Function pointer definition
		/// 
		using EventCallbackFn = std::function<void( Event& )>;

		/// 
		///  Destructor
		/// 
		virtual ~IWindow() {};
		
		/// 
		///  Sets the window data callback function pointer
		/// 
		inline virtual void SetEventCallback( const EventCallbackFn& callback ) = 0;
		
		/// 
		///  Updates window
		/// 
		virtual bool Update() = 0;

		/// 
		///  Sets vsync status
		/// 
		virtual void SetVSync( bool bEnable ) = 0;

		/// 
		///  Gets vsync status
		/// 
		virtual bool IsVSync( ) const = 0;

		/// 
		///  Gets window size
		/// 
		virtual const glm::ivec2 GetWindowSize() const = 0;

		/// 
		///  Gets native window ptr
		/// 
		virtual void* GetNativeWindow() const = 0;

		/// 
		///  Creates window
		/// 
		static IWindow* Create( const WindowProperties& props = WindowProperties() );
	
	};
}