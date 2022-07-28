workspace "Rengine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Dependencies
IncludeDir = {}
IncludeDir["GLFW"] = "Rengine/vendor/GLFW/include"
IncludeDir["Glad"] = "Rengine/vendor/Glad/include"
IncludeDir["ImGui"] = "Rengine/vendor/imgui"

group "Dependencies"
	include "Rengine/vendor/GLFW"
	include "Rengine/vendor/Glad"
	include "Rengine/vendor/imgui"

group ""

project "Rengine"
	location "Rengine"
	kind "SharedLib"
	language "C++"
        staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "repch.h"
	pchsource "Rengine/src/repch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"RE_PLATFORM_WINDOWS",
			"RE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
                runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
                runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
                runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Rengine/vendor"
	}

	links
	{
		"Rengine"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"RE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
                runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
                runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
                runtime "Release"
		optimize "On"
