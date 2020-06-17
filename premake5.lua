if os.istarget "Windows" then
	require "vstudio"
	local p = premake;
	local vc = p.vstudio.vc2010;
	
	function disableFastUpToDateCheck(prj, cfg)
		vc.element("DisableFastUpToDateCheck", nil, "true")
	end
	
	p.override(vc.elements, "globalsCondition",
			function(oldfn, prj, cfg)
				local elements = oldfn(prj, cfg)
				elements = table.join(elements, {disableFastUpToDateCheck})
				return elements
			end)
end

workspace "Gaia"
	architecture "x64"
	targetdir "build"
	
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
IncludeDir["ImGui"] = "Gaia/extern/ImGui"
IncludeDir["glm"] = "Gaia/extern/glm"

include "Gaia/extern/GLFW"
include "Gaia/extern/Glad"
include "Gaia/extern/ImGui"

project "Gaia"
	location "Gaia"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "gaia_pch.h"
	pchsource "%{prj.name}/src/gaia_pch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
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
		"%{prj.name}/extern/stb/include"
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
		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}
		

	filter "configurations:Debug"
		defines "GAIA_DEBUG"
		symbols "On"
				
	filter "configurations:Release"
		optimize "On"

project "Gaia_Sandbox"
	location "Gaia_Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	ignoredefaultlibraries { "libcmt" }
	
	debugdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("build-bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build-obj/" .. outputdir .. "/%{prj.name}")

	links 
	{ 
		"Gaia"
	}
	
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
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
		'{COPY} "../Gaia/assets" "%{cfg.targetdir}/assets"',
		'{COPY} "../Gaia_Sandbox/assets" "%{cfg.targetdir}/assets"'
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "GAIA_DEBUG"
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
		optimize "on"

		links
		{
			"Gaia/extern/assimp/bin/Release/assimp-vc141-mt.lib"
		}

		postbuildcommands 
		{
			'{COPY} "../Gaia/extern/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
		}
		