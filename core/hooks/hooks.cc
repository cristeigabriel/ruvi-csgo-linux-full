//
//  ruvi base
//

// includes
#include "hooks.hh"
#include "../../hacks/movement.hh"
#include "../../hacks/visuals.hh"
#include "../../menu/menu.hh"
#include "../../sdk/render/render.hh"
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
}

void hooks::paint::hooked(void *thisptr, paint_mode_t mode) {

  // call original function
  original(thisptr, mode);

  static void (*start_drawing)(void *) = reinterpret_cast<void (*)(void *)>(
      memory::find_pattern("vguimatsurface_client.so",
                           "55 48 89 E5 53 48 89 FB 48 83 EC 28 80 3D"));
  static void (*finish_drawing)(void *) = reinterpret_cast<void (*)(void *)>(
      memory::find_pattern("vguimatsurface_client.so", "55 31 FF 48 89 E5 53"));

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
}

int hooks::in_key_event::hooked(void *thisptr, int event_code, int key_num,
                                const char *current_binding) {

  if (vars::container["#window"]->get_state()) return 0;

  // call original function
  return original(thisptr, event_code, key_num, current_binding);
}

void hooks::lock_cursor::hooked(void *thisptr) {

  if (vars::container["#window"]->get_state()) {

    // unlock cursor
    csgo::vgui_surface->unlock_cursor();

    return;
  }

  // call original function
  original(thisptr);
}

bool hooks::create_move::hooked(void *thisptr, float sample_time,
                                c_user_cmd *cmd) {

  original(thisptr, sample_time, cmd);

  if (cmd || cmd->command_number) {

    movement.on_move(cmd);

    // save it for later
    qangle old_angle        = cmd->view_angles;
    float  old_side_move    = cmd->side_move;
    float  old_forward_move = cmd->forward_move;

    //
    //
    //

    utilities::move_fix(cmd, old_angle, old_forward_move, old_side_move);
  }
  return false;
}

void hooks::frame_stage_notify::hooked(void *               thisptr,
                                       client_frame_stage_t stage) {

  // call original function
  original(thisptr, stage);
}