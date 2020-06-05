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
IncludeDir["GLFW"] = "Gaia/extern/GLFW/include"
IncludeDir["Glad"] = "Gaia/extern/Glad/include"
IncludeDir["ImGui"] = "Gaia/extern/imgui"
IncludeDir["glm"] = "Gaia/extern/glm"
IncludeDir["stb_image"] = "Gaia/extern/stb_image"

group "Extern"
	include "Gaia/extern/GLFW"
	include "Gaia/extern/Glad"
	include "Gaia/extern/imgui"

group ""
	project "Gaia"
		location "Gaia"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		pchheader "gaia_pch.h"
		pchsource "Gaia/src/gaia_pch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
		}

		links 
		{ 
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

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
			"Gaia/extern",
			"%{IncludeDir.glm}"
		}

		links
		{
			"Gaia"
		}

		filter "system:windows"
			systemversion "latest"
		
		filter "configurations:Debug"
			defines "Gaia_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "Gaia_RELEASE"
			runtime "Release"
			optimize "on"
			
		
	
