#include "TyphoonPCH.h"
#include "WindowsTimestep.h"

#include "GLFW/glfw3.h"

namespace TyphoonEngine
{
	
	WindowsTimestep::WindowsTimestep()
	{
	}

	WindowsTimestep::~WindowsTimestep()
	{
	}

	float WindowsTimestep::GetSeconds() const
	{
		return static_cast<float>( glfwGetTime() );
	}

	int32_t WindowsTimestep::GetMilliseconds() const
	{
		return static_cast<float>( glfwGetTime() * 1000.f );
	}

}