workspace "OpenGL_Game"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "projects/Sandbox"

base_dir = "bin"
output_dir = (base_dir .. "/builds")
intermediates_dir = (base_dir .. "/intermediates")

external_dependencies = {}
external_dependencies["GLFW"] = "projects/libs/GLFW/include"
external_dependencies["Glad"] = "projects/libs/Glad/include"
external_dependencies["ImGui"] = "projects/libs/ImGui"
external_dependencies["glm"] = "projects/libs/glm"

include "projects/libs/GLFW"
include "projects/libs/Glad"
include "projects/libs/ImGui"

project "Sandbox"
    location "projects/Sandbox"
    kind "ConsoleApp"
    language "C++"   
    staticruntime "Off"
    cppdialect "C++20"
    systemversion "latest" 

    targetdir (output_dir .. "/%{cfg.system}_%{cfg.buildcfg}")
    objdir (intermediates_dir .. "/%{cfg.system}")

    pchheader "pch.h"
    pchsource "projects/Sandbox/src/pch.cpp"

    files {
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
    }

    includedirs {
        "projects/Sandbox/src",
        "projects/Sandbox/vendor",
        "%{external_dependencies.GLFW}",
        "%{external_dependencies.Glad}",
        "%{external_dependencies.ImGui}",
        "%{external_dependencies.glm}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows" 
        defines { "PLATFORM_WINDOWS" }   

    filter "system:linux"
        defines { "PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "PLATFORM_MAC" }

    filter "configurations:Debug"
        runtime "Debug"
        optimize "Off"
        symbols "On"
        defines {
            "CONFIGURATION_DEBUG"
        }   

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines {
            "CONFIGURATION_RELEASE"
        }   