workspace "Tusk"
	architecture "x86_64"
	startproject "Tusk.Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "External/GLFW/include"
IncludeDir["Glad"] = "External/Glad/include"
IncludeDir["ImGui"] = "External/ImGui"
IncludeDir["glm"] = "External/glm"
IncludeDir["stb_image"] = "External/stb"
IncludeDir["entt"] = "External/entt/include"
IncludeDir["xml"] = "External/pugixml"
IncludeDir["obj"] = "External/tiny"

group "Dependencies"
	include "External/GLFW"
	include "External/Glad"
	include "External/imgui"
	include "External/pugixml"
group ""

project "Tusk.Engine"
	location "Tusk.Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "tuskpch.h"
	pchsource "Tusk.Engine/tuskpch.cpp"

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.xml}",
		"%{IncludeDir.obj}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"pugiXML"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "Tusk.Sandbox"
	location "Tusk.Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Tusk.Engine/",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Tusk.Engine"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

