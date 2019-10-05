##
## project settings
## 

# cmake minimum version
cmake_minimum_required(VERSION 2.8)

# project name
project(ruvi)

# enable c++ 17
set(CMAKE_CXX_STANDARD 17)

#include directories (including fgui library includes)
include_directories(${CMAKE_SOURCE_DIR}/src)

# link fgui library (uncomment this if you are going to use the library instead of the source files)
#link_directories(${CMAKE_SOURCE_DIR}/src/FGUI)

# disable warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-narrowing")

# cheat source files
add_library(ruvi SHARED
        
        # cheat
        src/core/entry.cc
        src/core/hooks/hooks.cc
        src/core/interfaces/interfaces.cc
        src/hacks/visuals.cc
        src/menu/menu.cc
        src/sdk/input/input.cc
        src/sdk/memory/memory.cc
        src/sdk/netvars/netvars.cc
        src/sdk/render/render.cc
        
        # framework // remove this if you are going to use the library
        src/FGUI/controls/button.cc
        src/FGUI/controls/checkbox.cc
        src/FGUI/controls/colorlist.cc
        src/FGUI/controls/colorpicker.cc
        src/FGUI/controls/combobox.cc
        src/FGUI/controls/container.cc
        src/FGUI/controls/element.cc
        src/FGUI/controls/keybinder.cc
        src/FGUI/controls/label.cc
        src/FGUI/controls/listbox.cc
        src/FGUI/controls/multibox.cc
        src/FGUI/controls/slider.cc
        src/FGUI/controls/spinner.cc
        src/FGUI/controls/tabs.cc
        src/FGUI/controls/textbox.cc
        src/FGUI/handler/handler.cc
        src/FGUI/notifications/notifications.cc)

# link fgui library against the project (uncomment this if you are going to use the library instead of the source files)
#target_link_libraries(ruvi fgui)
