//
//  ruvi base
//

// includes
#include "interfaces.hh"
#include "sdk/memory/memory.hh"

void interfaces::on_entry_point() {

  // initialize exposed interfaces
  csgo::vgui_surface = interfaces::get_interface<i_surface>(
      STR("vguimatsurface_client.so->VGUI_Surface0"));
  csgo::vgui_panel =
      interfaces::get_interface<i_panel>(STR("vgui2_client.so->VGUI_Panel0"));
  csgo::engine_vgui = interfaces::get_interface<i_engine_vgui>(
      STR("engine_client.so->VEngineVGui0"));
  csgo::engine_client = interfaces::get_interface<i_engine_client>(
      STR("engine_client.so->VEngineClient0"));
  csgo::input_system = interfaces::get_interface<i_input_system>(
      STR("inputsystem_client.so->InputSystemVersion0"));
  csgo::input_internal = interfaces::get_interface<i_input_internal>(
      STR("vgui2_client.so->VGUI_InputInternal0"));
  csgo::debug_overlay = interfaces::get_interface<iv_debug_overlay>(
      STR("engine_client.so->VDebugOverlay0"));
  csgo::base_client = interfaces::get_interface<i_base_client_dll>(
      STR("client_panorama_client.so->VClient0"));
  csgo::entity_list = interfaces::get_interface<i_client_entity_list>(
      STR("client_panorama_client.so->VClientEntityList0"));
  csgo::cvar = interfaces::get_interface<i_cvar>(
      STR("materialsystem_client.so->VEngineCvar0"));
  csgo::material_system = interfaces::get_interface<i_material_system>(
      STR("materialsystem_client.so->VMaterialSystem0"));
  csgo::model_render = interfaces::get_interface<iv_model_render>(
      STR("engine_client.so->VEngineModel0"));
  csgo::model_info = interfaces::get_interface<c_model_info>(
      STR("engine_client.so->VModelInfoClient0"));
  csgo::render_view = interfaces::get_interface<c_render_view>(
      STR("engine_client.so->VEngineRenderView0"));
  csgo::prediction = interfaces::get_interface<i_prediction>(
      STR("client_panorama_client.so->VClientPrediction0"));
  csgo::engine_trace = interfaces::get_interface<i_engine_trace>(
      STR("engine_client.so->EngineTraceClient0"));

  // vfunc addresses
  std::uintptr_t hud_process_input_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[10]);
  std::uintptr_t get_local_player_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::engine_client)[12]);
  std::uintptr_t hud_update_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[11]);
  std::uintptr_t in_activate_mouse_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[16]);

  // pointers (addresses)
  i_client_mode *(*client_mode_ptr)() =
      reinterpret_cast<i_client_mode *(*)(void)>(
          memory::get_address(hud_process_input_vfunc + 0xB, 0x1, 0x5));
  c_base_client_state *(*client_state_ptr)(int) =
      reinterpret_cast<c_base_client_state *(*)(int)>(
          memory::get_address(get_local_player_vfunc + 0x9, 0x1, 0x5));
  c_global_vars *global_vars_ptr = *reinterpret_cast<c_global_vars **>(
      memory::get_address(hud_update_vfunc + 0xD, 0x3, 0x7));
  c_input *input_ptr = **reinterpret_cast<c_input ***>(
      memory::get_address(in_activate_mouse_vfunc, 0x3, 0x7));
  i_view_render *view_render_ptr =
      reinterpret_cast<i_view_render *>(memory::get_address(
          reinterpret_cast<std::uintptr_t>(memory::find_pattern(
              STR("client_panorama_client.so"), STR("55 48 8D 15 13 ?? ??"))) +
              0x126,
          0x3, 0x7));

  // initialize non exposed interfaces
  csgo::client_mode  = client_mode_ptr();
  csgo::client_state = client_state_ptr(-1);
  csgo::global_vars  = global_vars_ptr;
  csgo::input        = input_ptr;
  csgo::view_render  = view_render_ptr;
}