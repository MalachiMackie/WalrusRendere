workspace "WalrusRenderer"
    configurations {"Debug", "Release"}

    outputdir = "%{cfg.buildcfg}"

    include "vendor/GLFW"
    include "vendor/Glad"

    project "WalrusRenderer"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "off"

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "src/**.h",
            "src/**.cpp"
        }

        defines {
            "GLFW_INCLUDE_NONE"
        }

        includedirs {
            "src",
            "vendor/GLFW/include",
            "vendor/Glad/include"
        }

        links {
            "GLFW",
            "Glad",
            "dl",
            "pthread"
        }   
        
        filter "configurations:Debug"
            defines {"DEBUG"}
            symbols "On"

        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "ON"
    