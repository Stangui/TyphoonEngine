workspace "Typhoon"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Typhoon/ThirdParty/GLFW/include"

include "Typhoon/ThirdParty/GLFW"

project "Typhoon"
	location "Typhoon"
	kind "StaticLib"
	language "C++"
	
	targetdir ("%{prj.name}/bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("%{prj.name}/Intermediate/" .. outputdir .. "/%{prj.name}")
	
	pchheader ("TyphoonPCH.h")
	pchsource ("%{prj.name}/Src/%{prj.name}/TyphoonPCH.cpp")

	files
	{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/ThirdParty/SpdLog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",	
		"OpenGL32.lib"
	}

	filter "system:windows"
		cppdialect "C++11"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"TYPHOON_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "TYPHOON_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TYPHOON_RELEASE"
		symbols "On"
		optimize "On"
	
	filter "configurations:Shipping"
		defines "TYPHOON_SHIPPING"
		optimize "On"

			
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("Typhoon/bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("Typhoon/Intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs 
	{
		"Typhoon/src",
		"Typhoon/ThirdParty/spdlog/include"
	}
	
	links
	{
		"Typhoon"
	}
	
	filter "system:windows"
		cppdialect "C++11"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"TYPHOON_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "TYPHOON_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TYPHOON_RELEASE"
		symbols "On"
		optimize "On"
	
	filter "configurations:Shipping"
		defines "TYPHOON_SHIPPING"
		optimize "On"