project "24"  
    kind "ConsoleApp" 
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    
    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.txt"
    }

    filter "configurations:1 Example"
        defines { "DEBUG", "TEST", "PART1"}
        symbols "On"

    filter "configurations:1 Real"
        defines { "DEBUG", "PART1" }
        symbols "On"

    filter "configurations:1 Real Opt"
        defines { "NDEBUG", "PART1" }
        optimize "Speed"

        filter "configurations:2 Example"
        defines { "DEBUG", "TEST", "PART2"}
        symbols "On"

    filter "configurations:2 Real"
        defines { "DEBUG", "PART2" }
        symbols "On"

    filter "configurations:2 Real Opt"
        defines { "NDEBUG", "PART2" }
        optimize "Speed"

    