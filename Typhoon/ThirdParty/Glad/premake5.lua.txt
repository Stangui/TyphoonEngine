project "Glad"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/Glad/glad.h",
		"include/khr/khrplatform.h",
		"src/glad.c"
	}
	
	includedirs
	{
		"include"
	}

	filter "system:windows"
		buildoptions { "/std:c++14" }
		systemversion "latest"
		staticruntime "On"
				
		filter { "system:windows", "configurations:Release" }
			buildoptions "/MT"
		