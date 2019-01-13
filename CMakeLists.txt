cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)

project(ruvi-ui)
include_directories(src)

add_library(ruvi MODULE

        src/core/entry.cc
        src/interfaces/interfaces.cc
        src/utils/memory.cc
        src/hooks/hooks.cc
        src/utils/rendering.cc)