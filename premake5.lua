workspace "WalrusRenderer"
    configurations {"Debug", "Release"}

project "WalrusRenderer"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {"**.h", "**.cpp"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "ON"
    