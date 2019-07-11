#pragma once

#include "Core.h"
#include "TyphoonPCH.h"
#include "Events/ApplicationEvent.h"

namespace TyphoonEngine
{
	class Application
	{

	public:

		// Constructor
		Application();
		
		// Destructor
		virtual ~Application();
		
		// Update
		void Run();

		// Events
		void OnEvent( Event& Evt );

	private:

		std::unique_ptr<class IWindow> m_window;
		bool m_bRunning;
		bool m_bFocused;

	};

}

