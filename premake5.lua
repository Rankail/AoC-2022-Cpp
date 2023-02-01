workspace "AoC"
    startproject "01"
    architecture "x86_64"
    configurations { "1DT", "1DR", "1R", "2DT", "2DR", "2R" }

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

for i=1, 9 do
    include ("0"..i)
end
for i=10, 25 do
    include (""..i)
end