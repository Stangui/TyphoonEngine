#include "TyphoonPCH.h"
#include "GLFWInput.h"

#include "Typhoon/Application.h"
#include "Typhoon/IWindow.h"

#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	using namespace glm;

	std::unique_ptr<IInput> IInput::s_instance = std::unique_ptr<IInput>(new GLFWInput);

	//---------------------------------------------------------//
	bool GLFWInput::IsKeyPressedImpl( int32 keyCode ) const
	{
		const Application& app = Application::Get();
		if ( const IWindow* win = app.GetWindow() )
		{
			if ( auto* window = static_cast<GLFWwindow*>( win->GetNativeWindow() ) )
			{
				auto state = glfwGetKey( window, keyCode );
				return ( state == GLFW_PRESS || state == GLFW_REPEAT );
			}
		}

		return false;
	}

	//---------------------------------------------------------//
	bool GLFWInput::IsMouseButtonPressedImpl( int32 button ) const
	{
		const Application& app = Application::Get();
		if ( const IWindow* win = app.GetWindow() )
		{
			if ( auto* window = static_cast<GLFWwindow*>( win->GetNativeWindow() ) )
			{
				auto state = glfwGetMouseButton( window, button );
				return state == GLFW_PRESS;
			}
		}
		return false;
	}

	//---------------------------------------------------------//
	vec2 GLFWInput::GetMousePosImpl() const
	{
		const Application& app = Application::Get();
		if ( const IWindow* win = app.GetWindow() )
		{
			if ( auto* window = static_cast<GLFWwindow*>( win->GetNativeWindow() ) )
			{
				double x = 0.0, y = 0.0;
				glfwGetCursorPos( window, &x, &y );
				return vec2( static_cast<float>( x ), static_cast<float>( y ) );
			}
		}
		return vec2( 0.f );
	}

}