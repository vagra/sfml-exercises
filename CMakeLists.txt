cmake_minimum_required(VERSION 3.22)
project(SFMLExercises
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug")
set(CMAKE_DEBUG_POSTFIX "-d")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)

if(COMPILER_SUPPORTS_CXX20)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

find_package(SFML 2 REQUIRED COMPONENTS graphics system window network audio)
find_package(FMT REQUIRED)

if(SFML_FOUND)
    message ("sfml found")
else()
    message (FATAL_ERROR "Cannot find sfml")
endif()

if(FMT_FOUND)
    message ("fmt found")
else()
    message (FATAL_ERROR "Cannot find fmt")
endif()

add_subdirectory(hello)
add_subdirectory(world)
add_subdirectory(soldier)
add_subdirectory(grid)
add_subdirectory(dgrid)
add_subdirectory(viewer)
add_subdirectory(battle)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
