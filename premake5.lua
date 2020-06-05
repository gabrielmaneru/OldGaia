workspace "Gaia"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glm"] = "Gaia/extern/glm"

--group "Extern"
--	include "Gaia/extern/GLFW"
--	include "Gaia/extern/Glad"
--	include "Gaia/extern/imgui"

group ""
	project "Gaia"
		location "Gaia"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		--pchheader "gaia-pch.h"
		--pchsource "Gaia/src/gaia-pch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		includedirs
		{
			"%{prj.name}/src"
		}

		links 
		{ 
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{
			}

		filter "configurations:Debug"
			defines "GAIA_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "GAIA_RELEASE"
			runtime "Release"
			optimize "on"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Gaia/src",
			"Gaia/extern"
		}

		links
		{
			"Gaia"
		}

		filter "system:windows"
			systemversion "latest"
			
		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			optimize "on"
			
		
	
