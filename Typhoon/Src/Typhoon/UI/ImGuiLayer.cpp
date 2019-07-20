#include "TyphoonPCH.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "Typhoon/IWindow.h"
#include "Typhoon/Application.h"
#include "Typhoon/Input/KeyCodes.h"

#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace TyphoonEngine
{
	
	///--------------------------------------///
	ImGuiLayer::ImGuiLayer() : 
		 Layer("UILayer")
		,m_time(0.f)
	{
	}


	///--------------------------------------///
	ImGuiLayer::~ImGuiLayer()
	{
	}

	///--------------------------------------///
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			style.WindowRounding = 0.f;
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
		}

		const Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL( window, true );
		ImGui_ImplOpenGL3_Init( "#version 410" );
	}

	///--------------------------------------///
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
	///--------------------------------------///
	void ImGuiLayer::OnBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	///--------------------------------------///
	void ImGuiLayer::OnEnd()
	{
		ImGuiIO& io = ImGui::GetIO();
		const Application& app = Application::Get();
		io.DisplaySize = ImVec2( static_cast<float>(app.GetWindow()->GetWindowSize().x), static_cast<float>( app.GetWindow()->GetWindowSize().y ) );

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent( backup_current_context );
		}
	}

	///--------------------------------------///
	void ImGuiLayer::OnImGuiRender()
	{
	}
}