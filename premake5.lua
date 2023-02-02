workspace "AoC"
    startproject "01"
    architecture "x86_64"
    configurations { "1 Example", "1 Real", "1 Real Opt", "2 Example", "2 Real", "2 Real Opt" }

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