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
	IncludeDir["GLAD"] = "Typhoon/ThirdParty/Glad/include"

	include "Typhoon/ThirdParty/GLFW"
	include "Typhoon/ThirdParty/GLAD"

	project "Typhoon"
		location "Typhoon"
		kind "StaticLib"
		language "C++"
		
		targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
		objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
		
		pchheader ("TyphoonPCH.h")
		pchsource ("%{prj.name}/Src/TyphoonPCH.cpp")

		files
		{
			"%{prj.name}/Src/**.h",
			"%{prj.name}/Src/**.cpp"
		}
		
		includedirs 
		{
			"%{prj.name}/src",
			"%{prj.name}/ThirdParty/SpdLog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}"
		}
		
		links
		{
			"GLFW",	
			"GLAD",	
			"OpenGL32.lib",
			"gdi32"
		}

		filter "system:windows"
			cppdialect "C++11"
			staticruntime "On"
			systemversion "latest"
			
			defines
			{
				"TYPHOON_PLATFORM_WINDOWS",
				"GLFW_INCLUDE_NONE"
			}
			
		filter "configurations:Debug"
			defines "TYPHOON_DEBUG;TE_ASSERTS"
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
		
		targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
		objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
		
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