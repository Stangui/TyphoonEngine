#pragma once

#include "Event.h"

namespace TyphoonEngine
{

	// Base keyboard event, holds keycode
	class KeyEvent : public Event
	{
	public:

		inline int32 getKeyCode() const { return m_keyCode; }

		EVENT_CATEGORY( Input | Keyboard )

	protected:

		explicit KeyEvent( int32 keyCode ) : m_keyCode( keyCode )
		{
		}

	private:

		int32 m_keyCode;
	};

	// Key pressed event, holds additional repeated flag
	class KeyPressedEvent : KeyEvent
	{

	public:

		KeyPressedEvent( int32 keyCode, bool repeated ) : KeyEvent( keyCode ), m_bRepeated( repeated )
		{
		}

		std::string ToString() const
		{
			return "KeyPressed";
		}

		inline bool isRepeated() const { return m_bRepeated; }

		EVENT_TYPE( KeyPressed )

	private:

		bool m_bRepeated;
	};
	
	// Key released event
	class KeyReleasedEvent : KeyEvent
	{

	public:

		std::string ToString() const
		{
			return getName();
		}

		EVENT_TYPE( KeyReleased )
	};

}