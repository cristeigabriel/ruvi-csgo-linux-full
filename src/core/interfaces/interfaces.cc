//
//  ruvi base
//

// includes
#include "interfaces.hh"
#include "sdk/memory/memory.hh"

void interfaces::on_entry_point() {

  // initialize exposed interfaces
  csgo::vgui_surface = interfaces::get_interface<i_surface>(
      "vguimatsurface_client.so->VGUI_Surface0");
  csgo::vgui_panel =
      interfaces::get_interface<i_panel>("vgui2_client.so->VGUI_Panel0");
  csgo::engine_vgui = interfaces::get_interface<i_engine_vgui>(
      "engine_client.so->VEngineVGui0");
  csgo::engine_client = interfaces::get_interface<i_engine_client>(
      "engine_client.so->VEngineClient0");
  csgo::input_system = interfaces::get_interface<i_input_system>(
      "inputsystem_client.so->InputSystemVersion0");
  csgo::input_internal = interfaces::get_interface<i_input_internal>(
      "vgui2_client.so->VGUI_InputInternal0");
  csgo::debug_overlay = interfaces::get_interface<iv_debug_overlay>(
      "engine_client.so->VDebugOverlay0");
  csgo::base_client = interfaces::get_interface<i_base_client_dll>(
      "client_panorama_client.so->VClient0");
  csgo::entity_list = interfaces::get_interface<i_client_entity_list>(
      "client_panorama_client.so->VClientEntityList0");
  csgo::cvar = interfaces::get_interface<i_cvar>(
      "materialsystem_client.so->VEngineCvar0");
  csgo::material_system = interfaces::get_interface<i_material_system>(
      "materialsystem_client.so->VMaterialSystem0");

  // vfunc addresses
  std::uintptr_t hud_process_input_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[10]);
  std::uintptr_t get_local_player_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::engine_client)[12]);
  std::uintptr_t hud_update_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[11]);

  // pointers (addresses)
  i_client_mode *(*client_mode_ptr)() =
      reinterpret_cast<i_client_mode *(*)(void)>(
          memory::get_address(hud_process_input_vfunc + 11, 1, 5));
  c_base_client_state *(*client_state_ptr)(int) =
      reinterpret_cast<c_base_client_state *(*)(int)>(
          memory::get_address(get_local_player_vfunc + 9, 1, 5));

  // initialize non exposed interfaces
  csgo::client_mode = client_mode_ptr();
  csgo::client_state = client_state_ptr(-1);
  csgo::global_vars = *reinterpret_cast<c_global_vars **>(
      memory::get_address(hud_update_vfunc + 13, 3, 7));
}