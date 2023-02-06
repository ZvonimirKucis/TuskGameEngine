project "SoLoud"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    
    targetdir ("build/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    defines { "WITH_WINMM" }

    files
    {
        "src/audiosource/**.c*",
		"src/filter/**.c*",
		"src/core/**.c*"
    }

    includedirs
    {
        "src/**",
	    "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
