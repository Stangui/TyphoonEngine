#pragma once

#include "Event.h"

namespace TyphoonEngine 
{

	/// 
	///  Event called when window has been resized
	/// 
	class WindowResizeEvent : public Event
	{
	public:
		
		WindowResizeEvent( unsigned int width, unsigned int height )
			: m_Width( width )
			, m_Height( height ) {}

		/// 
		///  Returns window width
		/// 
		inline unsigned int GetWidth() const { return m_Width; }

		/// 
		///  Returns window height
		/// 
		inline unsigned int GetHeight() const { return m_Height; }

		/// 
		///  Debug string describing event
		/// 
		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d %d", GetName(), GetWidth(), GetHeight() );
			return msg;
		}

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( WindowResize )
		EVENT_CATEGORY( App )

	private:

		///  Window sizes
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		/// 
		///  Debug string describing event
		/// 
		virtual const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s", GetName() );
			return msg;
		}

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( WindowClose )
		EVENT_CATEGORY( App )
	};

	/// 
	///  Event called when window gains/loses focus
	/// 
	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool bFocused) : m_bFocused(bFocused) {}

		/// 
		///  Debug string describing event
		/// 
		virtual const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d", GetName(), m_bFocused );
			return msg;
		}

		/// 
		///  Returns whether window is focussed
		/// 
		inline bool IsFocused() const { return m_bFocused; }

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( WindowFocus )
		EVENT_CATEGORY( App )

	private:

		bool m_bFocused;
	};

	/// 
	///  Event called every frame tick
	/// 
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( AppTick )
		EVENT_CATEGORY( App )
	};

	/// 
	///  Event called every window update
	/// 
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( AppUpdate )
		EVENT_CATEGORY( App )
	};

	/// 
	///  Event every frame render
	/// 
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		/// 
		///  Register event type and flags
		/// 
		EVENT_TYPE( AppRender )
		EVENT_CATEGORY( App )
	};

}