cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)

project(ruvi-csgo-linux)
include_directories(src)

add_library(ruvi MODULE

        src/core/entry.cc
        src/framework/controls/controls.cc
        src/framework/input/input.cc
        src/framework/render/render.cc
        src/framework/window/window.cc
        src/hooks/hooks.cc
        src/interfaces/interfaces.cc
        src/memory/memory.cc)
