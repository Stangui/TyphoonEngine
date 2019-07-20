#include "TyphoonPCH.h"
#include "Timestep.h"

#include "Typhoon/Core.h"

#if TE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsTimestep.h"
#endif	////TE_PLATFORM_WINDOWS

namespace TyphoonEngine
{

	Timestep* Timestep::Create()
	{
#if TE_PLATFORM_WINDOWS
		return new WindowsTimestep();
#endif	////TE_PLATFORM_WINDOWS
#if TE_PLATFORM_LINUX
		return new LinuxTimestep();
#endif	////TE_PLATFORM_WINDOWS
#if TE_PLATFORM_MACOS
		return new MacOSTimestep();
#endif	////TE_PLATFORM_WINDOWS
		TE_ASSERT( false, "Unsupported timestep platform!" );
		return nullptr;
	}
}
