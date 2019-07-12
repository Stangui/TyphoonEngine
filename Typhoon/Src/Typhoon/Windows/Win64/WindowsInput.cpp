#include "TyphoonPCH.h"
#include "WindowsInput.h"

#include "Typhoon/Application.h"
#include "Typhoon/Windows/IWindow.h"

#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	std::unique_ptr<IInput> IInput::s_instance = std::unique_ptr<IInput>(new WindowsInput);

	bool WindowsInput::isKeyPressedImpl( int32 keyCode ) const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().getWindow()->GetNativeWindow() );
		auto state = glfwGetKey( window, keyCode );
		return ( state == GLFW_PRESS || state == GLFW_REPEAT );
	}

	bool WindowsInput::isMouseButtonPressedImpl( int32 button ) const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().getWindow()->GetNativeWindow() );
		auto state = glfwGetMouseButton( window, button );
		return state == GLFW_PRESS;
	}

	Vec2f WindowsInput::getMousePosImpl() const
	{
		auto* window = static_cast<GLFWwindow*>( Application::Get().getWindow()->GetNativeWindow() );
		double x, y;
		glfwGetCursorPos( window, &x, &y );
		return Vec2f( static_cast<float>( x ), static_cast<float>( y ) );
	}

}