#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/KeyboardEvent.h"
#include "Typhoon/Layers/LayerStack.h"

namespace TyphoonEngine
{
	class IWindow;

	class Application
	{

	public:

		// Constructor
		Application();

		// Destructor
		virtual ~Application();

		// Getters
		inline static const Application& Get() { return *s_instance; }
		inline const IWindow* GetWindow() const { return m_window.get(); }
		
		// Update
		void Run();

		// Events
		void OnEvent( Event& Evt );
		bool OnWindowClose( WindowCloseEvent& Evt );
		bool OnKeyPressed( KeyPressedEvent& Evt );

		//Layers
		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );
		void PopLayer( Layer* layer );
		void PopOverlay( Layer* layer );

	private:

		std::unique_ptr<class IWindow> m_window;
		class ImGuiLayer* m_imgui;
		bool m_bRunning;
		bool m_bFocused;
		LayerStack m_layerStack;

		// Singleton
		static Application* s_instance;

	};

}

