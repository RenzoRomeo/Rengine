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

include "Rengine/vendor/GLFW"
include "Rengine/vendor/Glad"
include "Rengine/vendor/imgui"

project "Rengine"
	location "Rengine"
	kind "SharedLib"
	language "C++"

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
		staticruntime "On"
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
                buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
                buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
                buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
                buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
                buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
                buildoptions "/MD"
		optimize "On"