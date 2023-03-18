cmake_minimum_required(VERSION 3.16)
project(VisionX)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(deps)

option(VISIONX_BUILD_TESTS "Build tests" OFF)

message(STATUS "VISIONX_BUILD_TESTS = ${VISIONX_BUILD_TESTS}")

message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(VISIONX_VERSION_MAJOR 0)
set(VISIONX_VERSION_MINOR 1)
set(VISIONX_VERSION_PATCH 0)

add_subdirectory(src)

if(VISIONX_BUILD_TESTS)
    add_subdirectory(tests)
endif()