cmake_minimum_required(VERSION 3.15)
project(samp-pathfinder CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_library(samp-pathfinder SHARED 
    src/main.cpp 
    src/natives.cpp
    src/worker.cpp
    src/pathfinder.cpp
    src/loader.cpp
    lib/samp-sdk/amx/amxplugin.cpp
)

target_compile_definitions(samp-pathfinder PRIVATE HAVE_STDINT_H)

target_include_directories(samp-pathfinder PRIVATE lib/samp-sdk src)