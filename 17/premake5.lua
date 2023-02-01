project "17"  
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

    prebuildcommands
    {
        ('{COPYFILE} "%{prj.location}src/*.txt" "%{wks.location}bin/"' .. outputdir .. '"/%{prj.name}"'),
    }

    filter "configurations:1DT"
        defines { "DEBUG", "TEST", "PART1"}
        symbols "On"

    filter "configurations:1DR"
        defines { "DEBUG", "PART1" }
        symbols "On"

    filter "configurations:1R"
        defines { "NDEBUG", "TIMEIT", "PART1" }
        optimize "Speed"

    filter "configurations:2DT"
        defines { "DEBUG", "TEST"}
        symbols "On"

    filter "configurations:2DR"
        defines { "DEBUG"}
        symbols "On"

    filter "configurations:2R"
        defines { "NDEBUG", "TIMEIT" }
        optimize "Speed"

    