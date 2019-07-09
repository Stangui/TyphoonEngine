#pragma once

#include "Core.h"

namespace TyphoonEngine
{

#define EVENT_CATEGORY(category) virtual int32 getCategoryFlags() const { return category; }
#define EVENT_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                         virtual EventType getEventType() const override { return getStaticType(); }\
                         virtual const char* getName() const override { return #type; }

	// Type of event 
	enum class EventType : uint8
	{
		AppInit, AppUpdate, AppClose,
		WindowClose, WindowFocus, WindowResized, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScroll
	};

	// Category of event
	enum EventCategory
	{
		None			= 0,
		Application		= BIT( 0 ),
		Input			= BIT( 1 ),
		Mouse			= BIT( 2 ),
		Keyboard		= BIT( 3 ),
		GameController  = BIT( 4 )
	};

	// Base class for an event
	class Event
	{

	public:

		// Returns type of this event
		virtual EventType getEventType() const = 0;
		
		// Returns the category this event belongs to
		virtual int32 getCategoryFlags() const = 0;
		
		// Gets event name
		virtual const char* getName() const = 0;

		// Returns whether this event is in the specified category
		inline bool isInCategory( EventCategory category )
		{
			return getCategoryFlags() & category;
		}

		// Returns a debug string event name
		virtual std::string ToString() const = 0;

	private:

		// Has event been handled?
		bool bHandled = false;
	};

	class EventDispatch
	{
		template<typename T>
		using EventFn = std::function<bool( T& )>;

	public:

		EventDispatch( Event& event ) : m_event( event )
		{

		}

		template<typename T>
		bool Dispatch( EventFn<T> func )
		{
			if ( m_event.GetEventType() == T::GetStaticType() )
			{
				m_event.bHandled = func( *(T*)&m_event );
				return true;
			}
			return false;
		}

	private:

		Event& m_event;
	};
}