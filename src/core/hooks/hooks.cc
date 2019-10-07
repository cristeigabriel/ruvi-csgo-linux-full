//
//  ruvi base
//

// includes
#include "hooks.hh"
#include "../../hacks/miscellaneous.hh"
#include "../../hacks/visuals.hh"
#include "../../menu/menu.hh"
#include "../../sdk/render/render.hh"
#include "../../sdk/utils/globals.hh"
#include "../../sdk/utils/utilities.hh"

// framework includes
#include <FGUI/FGUI.hh>

std::unique_ptr<vmt_hook> engine_vgui_hook  = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> base_client_hook  = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> vgui_surface_hook = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> client_mode_hook  = std::make_unique<vmt_hook>();

// originals
hooks::paint::fn *             hooks::paint::original;
hooks::in_key_event::fn *      hooks::in_key_event::original;
hooks::lock_cursor::fn *       hooks::lock_cursor::original;
hooks::create_move::fn *       hooks::create_move::original;
hooks::frame_stage_notify::fn *hooks::frame_stage_notify::original;

void hooks::on_entry_point() {
  try {

    if (engine_vgui_hook->initialize_and_hook_instance(csgo::engine_vgui))
      engine_vgui_hook->apply_hook<hooks::paint>(15);

    if (base_client_hook->initialize_and_hook_instance(csgo::base_client)) {
      base_client_hook->apply_hook<hooks::in_key_event>(21);
      base_client_hook->apply_hook<hooks::frame_stage_notify>(37);
    }

    if (vgui_surface_hook->initialize_and_hook_instance(csgo::vgui_surface))
      vgui_surface_hook->apply_hook<hooks::lock_cursor>(67);

    if (client_mode_hook->initialize_and_hook_instance(csgo::client_mode))
      client_mode_hook->apply_hook<hooks::create_move>(25);
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - entry point - hooks"));
  }
}

void hooks::paint::hooked(void *thisptr, paint_mode_t mode) {
  try {

    // call original function
    original(thisptr, mode);

    static void (*start_drawing)(void *) = reinterpret_cast<void (*)(void *)>(
        memory::find_pattern("vguimatsurface_client.so",
                             "55 48 89 E5 53 48 89 FB 48 83 EC 28 80 3D"));
    static void (*finish_drawing)(void *) =
        reinterpret_cast<void (*)(void *)>(memory::find_pattern(
            "vguimatsurface_client.so", "55 31 FF 48 89 E5 53"));

    if (mode & paint_mode_t::PAINT_UIPANELS) {

      start_drawing(csgo::vgui_surface);

      if (csgo::engine_client->is_in_game()) {

        // visuals
        visuals.on_paint();
      }

      // enable clipping before rendering the menu
      *csgo::vgui_surface->m_bClippingEnabled() = true;
      fgui::handler::render_window();
      *csgo::vgui_surface->m_bClippingEnabled() = false;

      finish_drawing(csgo::vgui_surface);
    }
  } catch (...) {

    std::throw_with_nested(std::runtime_error("error handler - paint - hooks"));
  }
}

int hooks::in_key_event::hooked(void *thisptr, int event_code, int key_num,
                                const char *current_binding) {
  try {

    if (vars::container["#window"]->get_state()) return 0;

    // call original function
    return original(thisptr, event_code, key_num, current_binding);
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - in key event - hooks"));
  }
}

void hooks::lock_cursor::hooked(void *thisptr) {
  try {

    if (vars::container["#window"]->get_state()) {

      // unlock cursor
      csgo::vgui_surface->unlock_cursor();

      return;
    }

    // call original function
    original(thisptr);
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - lock cursor - hooks"));
  }
}

bool hooks::create_move::hooked(void *thisptr, float sample_time,
                                c_user_cmd *cmd) {
  try {

    original(thisptr, sample_time, cmd);

    if (cmd || cmd->command_number) {

      // send packet (from Aimtux Fuzion)
      uintptr_t rbp;
      asm volatile("mov %%rbp, %0" : "=r"(rbp));
      bool *send_packet    = *reinterpret_cast<bool **>(rbp - 0x18);
      globals::send_packet = true;

      // miscellaneous
      miscellaneous.on_create_move(cmd);
    }
    return false;
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - create move - hooks"));
  }
}

void hooks::frame_stage_notify::hooked(void *               thisptr,
                                       client_frame_stage_t stage) {
  try {

    // call original function
    original(thisptr, stage);
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - frame stage notify - hooks"));
  }
}