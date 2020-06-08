workspace "Gaia"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release"
	}
	
	startproject "Gaia_Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Gaia/extern/GLFW/include"
IncludeDir["Glad"] = "Gaia/extern/Glad/include"
IncludeDir["ImGui"] = "Gaia/extern/imgui"
IncludeDir["glm"] = "Gaia/extern/glm"

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
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/extern",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.ImGui}",
			"%{prj.name}/extern/assimp/include",
			"%{prj.name}/extern/stb/include",
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
			
		
	
	project "Gaia_Sandbox"
		location "Gaia_Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		links
		{
			"Gaia"
		}
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.hpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/src/**.cpp"
		}
		
		includedirs
		{
			"%{prj.name}/src",
			"Gaia/src",
			"Gaia/extern",
			"%{IncludeDir.glm}"
		}
		
		postbuildcommands 
		{
			'{COPY} "../%{prj.name}/assets" "%{cfg.targetdir}/assets"'
		}


		filter "system:windows"
			systemversion "latest"
		
		filter "configurations:Debug"
			defines "Gaia_DEBUG"
			runtime "Debug"
			symbols "on"

			links
			{
				"Gaia/extern/assimp/bin/Debug/assimp-vc141-mtd.lib"
			}

			postbuildcommands 
			{
				'{COPY} "../Gaia/extern/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
			}

		filter "configurations:Release"
			defines "Gaia_RELEASE"
			runtime "Release"
			optimize "on"

			links
			{
				"Gaia/extern/assimp/bin/Release/assimp-vc141-mt.lib"
			}

			postbuildcommands 
			{
				'{COPY} "../Gaia/extern/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
			}
			
		
	
