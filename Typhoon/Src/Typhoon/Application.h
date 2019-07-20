#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/KeyboardEvent.h"
#include "Typhoon/Layers/LayerStack.h"

namespace TyphoonEngine
{
	class IWindow;
	class ImGuiLayer;

	namespace Renderers
	{
		class IVertexBuffer;
		class IIndexBuffer;
		class Shader;
		class VertexArray;
		class Camera;
	}

	//
	// Platform-agnostic application
	//
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

		// IWindow interface pointer
		std::unique_ptr<class IWindow> m_window;
		
		// GUI layer pointer
		ImGuiLayer* m_imgui;
		
		// Application flags
		bool m_bRunning : 1;
		bool m_bFocused : 1;
		
		// Layer stack
		LayerStack m_layerStack;

		//Temp GL rendering
		std::shared_ptr<Renderers::VertexArray> m_triangleVA;
		std::shared_ptr<Renderers::VertexArray> m_squareVA;
		std::shared_ptr<Renderers::Shader> m_vertexColorShader;
		std::shared_ptr<Renderers::Shader> m_blueShader;
		std::shared_ptr<Renderers::Camera> m_camera;

		// Singleton
		static Application* s_instance;

	};

}

