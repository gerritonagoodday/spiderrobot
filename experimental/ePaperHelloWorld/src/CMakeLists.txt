# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
cmake_minimum_required(VERSION 3.16.0)
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
idf_component_register(SRCS ${app_sources})


