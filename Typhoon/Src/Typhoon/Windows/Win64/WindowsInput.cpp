#include "TyphoonPCH.h"
#include "WindowsInput.h"

#include "Typhoon/Application.h"
#include "Typhoon/Windows/IWindow.h"

#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	using namespace glm;

	std::unique_ptr<IInput> IInput::s_instance = std::unique_ptr<IInput>(new WindowsInput);

	bool WindowsInput::IsKeyPressedImpl( int32 keyCode ) const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().GetWindow()->GetNativeWindow() );
		auto state = glfwGetKey( window, keyCode );
		return ( state == GLFW_PRESS || state == GLFW_REPEAT );
	}

	bool WindowsInput::IsMouseButtonPressedImpl( int32 button ) const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().GetWindow()->GetNativeWindow() );
		auto state = glfwGetMouseButton( window, button );
		return state == GLFW_PRESS;
	}

	vec2 WindowsInput::GetMousePosImpl() const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().GetWindow()->GetNativeWindow() );
		double x, y;
		glfwGetCursorPos( window, &x, &y );
		return vec2( static_cast<float>( x ), static_cast<float>( y ) );
	}

}