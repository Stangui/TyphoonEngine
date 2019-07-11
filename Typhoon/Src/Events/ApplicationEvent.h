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

		std::string ToString() const override
		{
			return getName();
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

		virtual std::string ToString() const override
		{
			return getName();
		}

		EVENT_TYPE( WindowClose )
		EVENT_CATEGORY( App )
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(bool bFocused) : m_bFocused(bFocused) {}

		virtual std::string ToString() const override
		{
			return getName();
		}

		inline bool isFocused() const { return m_bFocused; }

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