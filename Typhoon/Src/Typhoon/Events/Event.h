#pragma once

#include "TyphoonPCH.h"
#include "Typhoon/Core.h"

namespace TyphoonEngine
{

#define EVENT_CATEGORY(category) virtual glm::int32 GetCategoryFlags() const { return category; }
#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                         virtual EventType GetEventType() const override { return GetStaticType(); }\
                         virtual const char* GetName() const override { return #type; }

	// Type of event 
	enum class EventType : glm::uint8
	{
		AppInit, AppUpdate, AppRender, AppClose, AppTick,
		WindowClose, WindowFocus, WindowResize, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScroll
	};

	// Category of event
	enum EventCategory
	{
		None			= 0,
		App				= BIT( 0 ),
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
		virtual EventType GetEventType() const = 0;
		
		// Returns the category this event belongs to
		virtual glm::int32 GetCategoryFlags() const = 0;
		
		// Gets event name
		virtual const char* GetName() const = 0;

		// Returns whether this event is in the specified category
		inline bool IsInCategory( EventCategory category )
		{
			return GetCategoryFlags() & category;
		}

		// Returns a debug string event name
		virtual const std::string ToString() const = 0;

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
				return m_event.bHandled = func( *(T*)&m_event );
			}
			return false;
		}

	private:

		Event& m_event;
	};

	inline std::ostream& operator<<( std::ostream& os, const Event& Evt )
	{
		return os << Evt.ToString();
	}

}