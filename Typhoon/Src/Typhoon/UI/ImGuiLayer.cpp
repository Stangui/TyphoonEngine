#include "TyphoonPCH.h"
#include "ImGuiLayer.h"

#include "Typhoon/Windows/IWindow.h"
#include "Typhoon/Application.h"
#include "Typhoon/InputCodes/KeyCodes.h"
#include "Typhoon/Platform/OpenGL/imguiopengl3renderer.h"
#include "imgui.h"
#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	
	//--------------------------------------//
	ImGuiLayer::ImGuiLayer() : 
		 Layer("UILayer")
		,m_time(0.f)
	{
	}


	//--------------------------------------//
	ImGuiLayer::~ImGuiLayer()
	{
	}

	//--------------------------------------//
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = TE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = TE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = TE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = TE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = TE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = TE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = TE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = TE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = TE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = TE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = TE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = TE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = TE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = TE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = TE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = TE_KEY_A;
		io.KeyMap[ImGuiKey_C] = TE_KEY_C;
		io.KeyMap[ImGuiKey_V] = TE_KEY_V;
		io.KeyMap[ImGuiKey_X] = TE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = TE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = TE_KEY_Z;

		ImGui_ImplOpenGL3_Init( "#version 410" );
	}

	//--------------------------------------//
	void ImGuiLayer::OnDetach()
	{
	}

	//--------------------------------------//
	void ImGuiLayer::OnUpdate()
	{
		const Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		if ( const IWindow* win = app.GetWindow() )
		{
			io.DisplaySize = ImVec2( static_cast<float>( app.GetWindow()->GetWindowSize().x ), static_cast<float>( app.GetWindow()->GetWindowSize().y ) );
		}

		float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = ( m_time > 0.f ) ? ( m_time - time ) : 1.f / 60.f;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow( &show );
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
	}

	//--------------------------------------//
	void ImGuiLayer::OnEvent(Event& Evt)
	{
	}

}