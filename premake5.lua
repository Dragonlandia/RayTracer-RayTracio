workspace "RayTracer"
	architecture "x86"
	configurations { "Debug", "Release" }
	targetdir "bin/%{cfg.buildcfg}"

	project "RayTracer"
		location "RayTracer"
		kind "ConsoleApp"
		language "C++"

		files
		{
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.h"
		}