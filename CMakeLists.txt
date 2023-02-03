cmake_minimum_required(VERSION 3.9)
project(SFMLExercises
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_DEBUG_POSTFIX "-d")

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug)
endif()
message("build: $(CMAKE_BUILD_TYPE)")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

if(COMPILER_SUPPORTS_CXX17)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
