//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <dlfcn.h>

// interfaces
#include "valve/isurface.hh"
#include "valve/ipanel.hh"
#include "valve/ienginevgui.hh"
#include "valve/iengineclient.hh"
#include "valve/iinputsystem.hh"

// prototypes
typedef void* (* create_interface_fn)( const char*, int* );

namespace interfaces {

    void on_entry_point();

    template<typename interface>

    interface* get_interface(const char* file_name, const char* version) {
        void* library = dlopen(file_name, RTLD_NOLOAD | RTLD_NOW);

        if (!library)
            return nullptr;

        void* create_interface_sym = dlsym(library, "CreateInterface");

        // if the interface version doesn't match, return NULL
        if (!create_interface_sym)
            return nullptr;

        create_interface_fn factory = reinterpret_cast<create_interface_fn>(create_interface_sym);

        return reinterpret_cast<interface*>(factory(version, nullptr));
    }
}

namespace csgo {

   extern i_surface* vgui_surface;
   extern i_panel* vgui_panel;
   extern i_engine_vgui* engine_vgui;
   extern i_engine_client* engine_client;
   extern i_input_system* input_system;
}