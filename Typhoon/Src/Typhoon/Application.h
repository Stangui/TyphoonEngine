#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/KeyboardEvent.h"

namespace TyphoonEngine
{
	class IWindow;

	class Application
	{

	public:

		// Constructor
		Application();
		
		// Getters
		inline static const Application& Get() { return *s_instance; }
		inline const IWindow* getWindow() const { return m_window.get(); }

		// Destructor
		virtual ~Application();
		
		// Update
		void Run();

		// Events
		void OnEvent( Event& Evt );
		bool OnWindowClose( WindowCloseEvent& Evt );
		bool OnKeyPressed( KeyPressedEvent& Evt );

	private:

		std::unique_ptr<class IWindow> m_window;
		bool m_bRunning;
		bool m_bFocused;
		static Application* s_instance;

	};

}

