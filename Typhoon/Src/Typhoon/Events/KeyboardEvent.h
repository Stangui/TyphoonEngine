#pragma once

#include "Event.h"

namespace TyphoonEngine
{

	///  Base keyboard event, holds keycode
	class KeyEvent : public Event
	{
	public:

		inline glm::int32 GetKeyCode() const { return m_keyCode; }

		EVENT_CATEGORY( Input | Keyboard )

	protected:

		explicit KeyEvent( glm::int32 keyCode ) : m_keyCode( keyCode )
		{
		}

	private:

		glm::int32 m_keyCode;
	};

	///  Key pressed event, holds additional repeated flag
	class KeyPressedEvent : public KeyEvent
	{

	public:

		KeyPressedEvent( glm::int32 keyCode, bool repeated ) : KeyEvent( keyCode ), m_bRepeated( repeated )
		{
		}

		const std::string ToString() const
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d (%d)", GetName(), GetKeyCode(), m_bRepeated );
			return msg;
		}

		inline bool IsRepeated() const { return m_bRepeated; }

		EVENT_TYPE( KeyPressed )

	private:

		bool m_bRepeated;
	};
	
	///  Key released event
	class KeyReleasedEvent : public KeyEvent
	{

	public:

		KeyReleasedEvent( glm::int32 keyCode ) : KeyEvent( keyCode )
		{
		}

		const std::string ToString() const
		{
			char msg[256];
			sprintf_s( msg, 256, "%s : %d", GetName(), GetKeyCode() );
			return msg;
		}

		EVENT_TYPE( KeyReleased )
	};

}