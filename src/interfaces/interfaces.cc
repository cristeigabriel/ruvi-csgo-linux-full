//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "interfaces.hh"

void interfaces::on_entry_point() {

    auto surface_module = "./bin/linux64/vguimatsurface_client.so";
    auto vgui2_module = "./bin/linux64/vgui2_client.so";
    auto engine_module = "./bin/linux64/engine_client.so";
    auto inputsystem_module = "./bin/linux64/inputsystem_client.so";

    csgo::vgui_surface = interfaces::get_interface<i_surface>( surface_module, "VGUI_Surface031" );
    csgo::vgui_panel = interfaces::get_interface<i_panel>( vgui2_module, "VGUI_Panel009" );
    csgo::engine_vgui = interfaces::get_interface<i_engine_vgui>( engine_module, "VEngineVGui001" );
    csgo::engine_client = interfaces::get_interface<i_engine_client>( engine_module, "VEngineClient014" );
    csgo::input_system = interfaces::get_interface<i_input_system>( inputsystem_module, "InputSystemVersion001" );
    csgo::input_internal = interfaces::get_interface<i_input_internal>( vgui2_module, "VGUI_InputInternal001" );
}

namespace csgo {

    i_surface* vgui_surface;
    i_panel* vgui_panel;
    i_engine_vgui* engine_vgui;
    i_engine_client* engine_client;
    i_input_system* input_system;
    i_input_internal* input_internal;
}