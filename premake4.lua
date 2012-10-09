-- A solution contains projects, and defines the available configurations
solution "Sketch"
  configurations { "Debug", "Release" }
  
  project "Sample"
    kind "ConsoleApp"
    language "C++"
    files {"*.hpp", "*.cpp"}
    includedirs {"."}
    links{'OpenCL', 'gts', 'noise','glib-2.0'}
    buildoptions {"`pkg-config --libs --cflags glib-2.0` --std=c++11" } ---Wall -Wextra
    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
