project "pugiXML"
	kind "StaticLib"
	language "C++"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"pugiconfig.hpp",
		"pugixml.cpp",
		"pugixml.hpp"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"pugiconfig.hpp",
			"pugixml.cpp",
			"pugixml.hpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
