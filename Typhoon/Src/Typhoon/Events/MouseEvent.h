#pragma once

#include "Event.h"

namespace TyphoonEngine
{
	// Mouse move event, holds x,y mouse coordinates
	class MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent( float x, float y ) : m_mouseX( x ), m_mouseY( y )
		{
		}

		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %.1f %.1f", getName(), m_mouseX, m_mouseY );
			return msg;
		}

		inline void getPosition( float& x, float& y ) const
		{
			x = m_mouseX;
			y = m_mouseY;
		}

		EVENT_CATEGORY( Input | Mouse )
		EVENT_TYPE( MouseMoved )
			
	private:

		float m_mouseX;
		float m_mouseY;
	};

	class MouseButtonEvent : public Event
	{
	public:

		inline int32 getButtonId() const
		{
			return m_buttonId;
		}

		EVENT_CATEGORY( Mouse | Input )

	protected:

		explicit MouseButtonEvent( int32 id ) : m_buttonId( id )
		{
		}

	private:

		int32 m_buttonId;
	};

	class MouseButtonPressed : public MouseButtonEvent
	{
	public:

		explicit MouseButtonPressed( int32 id ) : MouseButtonEvent( id )
		{
		}

		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d", getName(), getButtonId() );
			return msg;
		}

		EVENT_TYPE( MouseButtonPressed )
	};

	class MouseButtonReleased : public MouseButtonEvent
	{
	public:

		explicit MouseButtonReleased( int32 id ) : MouseButtonEvent( id )
		{
		}

		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d", getName(), getButtonId() );
			return msg;
		}

		EVENT_TYPE( MouseButtonReleased )
	};

	class MouseScroll : public Event
	{
	public:

		MouseScroll( float x, float y ) : m_offsetX( x ), m_offsetY( y )
		{
		}

		const std::string ToString() const override
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %.1f %.1f", getName(), m_offsetX, m_offsetY );
			return msg;
		}

		inline void getScrollOffsets( float& x, float& y ) const { x = m_offsetX; y = m_offsetY; }

		EVENT_CATEGORY( Input | Mouse )
		EVENT_TYPE( MouseScroll )
	
	private:

		float m_offsetX;
		float m_offsetY;
	};

}