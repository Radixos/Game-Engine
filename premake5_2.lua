workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debud",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
	location "Engine"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filters "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion"10.0.18362.0"

		defines
		{
			"NG_PLATFORM_WINDOWS",
			"NG_DEBUG"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debud"
		defines "ENG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENG_DIST"
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
		"%{prj.name}/vendor/spdlog/include"
		"Engine/src"
	}

	links
	{
		"Engine"
	}

	filters "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion"10.0.18362.0"

		defines
		{
			"NG_PLATFORM_WINDOWS",
		}

	filter "configurations:Debud"
		defines "ENG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENG_DIST"
		optimize "On"