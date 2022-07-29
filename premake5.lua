workspace "Rengine"
	architecture "x64"
    startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Dependencies
IncludeDir = {}
IncludeDir["GLFW"] = "Rengine/vendor/GLFW/include"
IncludeDir["Glad"] = "Rengine/vendor/Glad/include"
IncludeDir["ImGui"] = "Rengine/vendor/imgui"
IncludeDir["glm"] = "Rengine/vendor/glm"

group "Dependencies"
	include "Rengine/vendor/GLFW"
	include "Rengine/vendor/Glad"
	include "Rengine/vendor/imgui"

group ""

project "Rengine"
	location "Rengine"
	kind "StaticLib"
	language "C++"
    cppdialect "C++20"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "repch.h"
	pchsource "Rengine/src/repch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
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
			"RE_PLATFORM_WINDOWS",
			"RE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
        runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RE_RELEASE"
        runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RE_DIST"
        runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Rengine/vendor/spdlog/include",
		"Rengine/src",
		"Rengine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Rengine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
        runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RE_RELEASE"
        runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RE_DIST"
        runtime "Release"
		optimize "on"
