project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

	targetdir ("build-bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "src/glad.c"
    }

    includedirs
	{
        "include"
    }
    
	filter "system:windows"
        systemversion "latest"
