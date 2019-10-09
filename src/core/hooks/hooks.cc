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

// declare pointers
std::unique_ptr<vmt_hook> engine_vgui_hook  = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> base_client_hook  = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> vgui_surface_hook = std::make_unique<vmt_hook>();
std::unique_ptr<vmt_hook> client_mode_hook  = std::make_unique<vmt_hook>();

// declare original
decltype( &hooks::paint::hooked )              hooks::paint::original              = nullptr;
decltype( &hooks::in_key_event::hooked )       hooks::in_key_event::original       = nullptr;
decltype( &hooks::lock_cursor::hooked )        hooks::lock_cursor::original        = nullptr;
decltype( &hooks::create_move::hooked )        hooks::create_move::original        = nullptr;
decltype( &hooks::frame_stage_notify::hooked ) hooks::frame_stage_notify::original = nullptr;

void hooks::on_entry_point() {
  CODE_START

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
  CODE_END("error handler - entry point - hooks")
}

void hooks::paint::hooked(void *thisptr, paint_mode_t mode) {
  CODE_START

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
  CODE_END("error handler - paint - hooks")
}

int hooks::in_key_event::hooked(void *thisptr, int event_code, int key_num,
                                const char *current_binding) {
  CODE_START

    if (vars::container["#window"]->get_state()) return 0;

    // call original function
    return original(thisptr, event_code, key_num, current_binding);
  CODE_END("error handler - in key event - hooks")
}

void hooks::lock_cursor::hooked(void *thisptr) {
  CODE_START

    if (vars::container["#window"]->get_state()) {

      // unlock cursor
      csgo::vgui_surface->unlock_cursor();

      return;
    }

    // call original function
    original(thisptr);
  CODE_END("error handler - lock cursor - hooks")
}

bool hooks::create_move::hooked(void *thisptr, float sample_time,
                                c_user_cmd *cmd) {
  CODE_START

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
  CODE_END("error handler - create move - hooks")
}

void hooks::frame_stage_notify::hooked(void *               thisptr,
                                       client_frame_stage_t stage) {
  CODE_START
  
    // call original function
    original(thisptr, stage);
  CODE_END("error handler - frame stage notify - hooks")
}
