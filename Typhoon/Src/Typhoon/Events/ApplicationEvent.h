#pragma once

#include "Event.h"

namespace TyphoonEngine 
{

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent( unsigned int width, unsigned int height )
			: m_Width( width ), m_Height( height ) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d %d", GetName(), GetWidth(), GetHeight() );
			return msg;
		}

		EVENT_TYPE( WindowResize )
		EVENT_CATEGORY( App )
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		virtual const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s", GetName() );
			return msg;
		}

		EVENT_TYPE( WindowClose )
		EVENT_CATEGORY( App )
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool bFocused) : m_bFocused(bFocused) {}

		virtual const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d", GetName(), m_bFocused );
			return msg;
		}

		inline bool IsFocused() const { return m_bFocused; }

		EVENT_TYPE( WindowFocus )
		EVENT_CATEGORY( App )

	private:

		bool m_bFocused;
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_TYPE( AppTick )
		EVENT_CATEGORY( App )
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_TYPE( AppUpdate )
		EVENT_CATEGORY( App )
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_TYPE( AppRender )
		EVENT_CATEGORY( App )
	};

}