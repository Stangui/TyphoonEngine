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
			return getName();
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

	class MouseButtonEvent : Event
	{
	public:

		inline uint8 getButtonId() 
		{
			return m_buttonId;
		}

		EVENT_CATEGORY( Mouse | Input )

	protected:

		explicit MouseButtonEvent( uint8 id ) : m_buttonId( Id )
		{
		}

	private:

		uint8 m_buttonId;
	};

	class MouseButtonPressed : MouseButtonEvent
	{
	public:

		explicit MouseButtonPressed( uint8 buttonId ) : MouseButtonEvent( buttonId )
		{
		}

		const std::string ToString() const override
		{
			return getName();
		}

		EVENT_TYPE( MousePressed )
	};

	class MouseButtonReleased : Event
	{
	public:

		explicit MouseButtonReleased( uint8 buttonId ) : MouseButtonEvent( buttonId )
		{
		}

		const std::string ToString() const override
		{
			return getName();
		}

		EVENT_TYPE( MouseReleased )
	};

	class MouseScroll : Event
	{
	public:

		MouseScroll( float x, float y ) : m_offsetX( x ), m_offsetY( y )
		{
		}

		const std::string ToString() const override
		{
			return getName();
		}

		inline void getScrollOffsets( float& x, float& y ) const { x = m_offsetX; y = m_OffsetY; }

		EVENT_CATEGORY( Input | Mouse )
		EVENT_TYPE( MouseScrolled )
	
	private:

		float m_offsetX;
		float m_offsetY;
	};

}