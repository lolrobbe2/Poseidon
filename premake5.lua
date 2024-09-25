newoption {
    trigger = "enable-WSL",
    description = "enable Windows Subsytem For linux building",
    category    = "Build Options"
}

newoption {
    trigger = "no-sandbox",
    description = "disable sandbox project",
    category    = "Build Options"
}

newoption {
    trigger = "project-include",
    description = "disable seperate project workspace",
    category    = "Build Options"
}

newoption {
    trigger     = "lib-type",
    value       = "LIB-TYPE",
    description = "Choose a library type Shared or static",
    default     = "SharedLib",
    category    = "project Options",
    allowed = {
        { "SharedLib","Shared"},
        { "StaticLib","Static"}
    }
}


flags
{
    "MultiProcessorCompile"
}


if not _OPTIONS["project-include"] then
startproject "sandbox"
workspace "Poseidon"
    architecture "x64"
    
    configurations
    {
        "debug",
        "release",
        "distribution"
    }
end
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Poseidon"] =  "%{prj.location}/src"

group"core"
project "Poseidon"
    location "Poseidon"
    kind(_OPTIONS["lib-type"])
    language "c++"
    targetdir("%{wks.location}/bin/" .. outputdir .. "/x64/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/x64/%{prj.name}")
    files
    {
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
    }
    includedirs
    {
        "%{IncludeDir.Poseidon}"
    }
    if _OPTIONS["lib-type"] == "Shared" or _OPTIONS["lib-type"] == "SharedLib" then
        defines 
        {
            "PD_BUILD_DLL"
        }
    end
  
    
    filter "system:windows"
        cppdialect "c++20"
        systemversion "latest"
        links
        {
        }
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"

    filter "system:linux"
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"
    if _OPTIONS["enable-WSL"] then
        toolchainversion "wsl2"
    end
if not _OPTIONS["no-sandbox"] then
group"SANDBOX"
project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "c++"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/x64/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/x64/%{prj.name}")
    includedirs
    {
        "../Poseidon/Poseidon/src"
    }
    links
    {
        "Poseidon"
    }
    files
    {
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
    }
    filter "system:windows"
        cppdialect "c++20"
        systemversion "latest"
        links
        {
        }
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"

    filter "system:linux"
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"
    if _OPTIONS["enable-WSL"] then
        toolchainversion "wsl2"
    end
end