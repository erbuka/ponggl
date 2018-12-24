workspace "PongGL"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    system "windows"

    filter "system:windows"
        systemversion "latest"

project "PongGL"
    kind "ConsoleApp"
    language "C++" 
    location "PongGL"

    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    debugdir "bin/%{cfg.buildcfg}/%{prj.name}"

    files { "%{prj.name}/**.h", "%{prj.name}/**.cpp" }
    includedirs { "vendor/freeglut/include", "vendor/glew/include" }
    libdirs { "vendor/freeglut/lib", "vendor/glew/lib" }
    defines { "GLEW_STATIC" }
    links { "glew32s", "freeglut", "opengl32" }

    postbuildcommands {
        "{COPY} models/ ../bin/%{cfg.buildcfg}/%{prj.name}/models",
        "{COPY} shaders/ ../bin/%{cfg.buildcfg}/%{prj.name}/shaders",
        "{COPY} textures/ ../bin/%{cfg.buildcfg}/%{prj.name}/textures",
        "{COPY} ../vendor/freeglut/bin/freeglut.dll ../bin/%{cfg.buildcfg}/%{prj.name}"
    }    

    filter "configurations:Debug"
        optimize "Off"
        symbols "On"
        defines "DEBUG"

    filter "configurations:Release"
        optimize "On"
        symbols "Off"
        defines "NDEBUG"


