//
//  ruvi base
//

// includes
#include "../../core/definitions/handler.hh"
#include "../../hacks/miscellaneous.hh"
#include "../../hacks/visuals.hh"
#include "../../menu/menu.hh"
#include "../../sdk/render/render.hh"
#include "../../sdk/utils/globals.hh"
#include "../../sdk/utils/utilities.hh"
#include "hooks.hh"

// framework includes
#include <FGUI/FGUI.hh>

// declare objects (global objects, no need
//                  to wrap them in smart pointers)
static vmt_hook engine_vgui_hook;
static vmt_hook base_client_hook;
static vmt_hook vgui_surface_hook;
static vmt_hook client_mode_hook;
static vmt_hook model_render_hook;
static vmt_hook view_render_hook;

// declare originals
decltype(&hooks::paint::hooked)        hooks::paint::original;
decltype(&hooks::in_key_event::hooked) hooks::in_key_event::original;
decltype(&hooks::lock_cursor::hooked)  hooks::lock_cursor::original;
decltype(&hooks::create_move::hooked)  hooks::create_move::original;
decltype(
    &hooks::frame_stage_notify::hooked) hooks::frame_stage_notify::original;
decltype(
    &hooks::draw_model_execute::hooked) hooks::draw_model_execute::original;
decltype(&hooks::override_view::hooked) hooks::override_view::original;
decltype(&hooks::render_view::hooked)   hooks::render_view::original;

void hooks::on_entry_point() {

  CODE_START

  if (engine_vgui_hook.initialize_and_hook_instance(csgo::engine_vgui))
    engine_vgui_hook.apply_hook<hooks::paint>(15);

  if (base_client_hook.initialize_and_hook_instance(csgo::base_client)) {
    base_client_hook.apply_hook<hooks::in_key_event>(21);
    base_client_hook.apply_hook<hooks::frame_stage_notify>(37);
  }

  if (vgui_surface_hook.initialize_and_hook_instance(csgo::vgui_surface))
    vgui_surface_hook.apply_hook<hooks::lock_cursor>(67);

  if (client_mode_hook.initialize_and_hook_instance(csgo::client_mode)) {
    client_mode_hook.apply_hook<hooks::create_move>(25);
    client_mode_hook.apply_hook<hooks::override_view>(19);
  }

  if (model_render_hook.initialize_and_hook_instance(csgo::model_render))
    model_render_hook.apply_hook<hooks::draw_model_execute>(21);

  if (view_render_hook.initialize_and_hook_instance(csgo::view_render))
    view_render_hook.apply_hook<hooks::render_view>(6);

  CODE_END(STR("error handler - entry point - hooks"));
}

void hooks::paint::hooked(void *thisptr, paint_mode_t mode) {

  CODE_START

  // call original function
  original(thisptr, mode);

  static void (*start_drawing)(void *) = reinterpret_cast<void (*)(void *)>(
      memory::find_pattern(STR("vguimatsurface_client.so"),
                           STR("55 48 89 ?? 53 ?? 89 FB 48 ?? EC 28 80 3D")));
  static void (*finish_drawing)(void *) =
      reinterpret_cast<void (*)(void *)>(memory::find_pattern(
          STR("vguimatsurface_client.so"), STR("55 31 FF 48 89 E5 53")));

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

  CODE_END(STR("error handler - paint - hooks"));
}

int hooks::in_key_event::hooked(void *thisptr, int event_code, int key_num,
                                const std::string_view current_binding) {
  CODE_START

  if (vars::container["#window"]->get_state()) return 0;

  // call original function
  return original(thisptr, event_code, key_num, current_binding);

  CODE_END(STR("error handler - in key event - hooks"));
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

  CODE_END(STR("error handler - lock cursor - hooks"))
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

  CODE_END(STR("error handler - create move - hooks"))
}

void hooks::frame_stage_notify::hooked(void *               thisptr,
                                       client_frame_stage_t stage) {
  CODE_START

  // call original function
  original(thisptr, stage);

  CODE_END(STR("error handler - frame stage notify - hooks"))
}

void hooks::override_view::hooked(void *thisptr, c_view_setup *view_setup) {

  CODE_START

  if (csgo::engine_client->is_in_game()) {

    // visuals
    visuals.on_override_view(view_setup);
  }

  // call original function
  original(thisptr, view_setup);

  CODE_END(STR("error handler - override view - hooks"))
}

void hooks::draw_model_execute::hooked(void *                     thisptr,
                                       i_mat_render_context *     context,
                                       void *                     state,
                                       const model_render_info_t &info,
                                       matrix3x4_t *custom_bone_to_world) {
  CODE_START

  // check if something is trying to override the chams material and call
  // original (glow fix)
  if (csgo::model_render->is_forced_material_override())
    original(thisptr, context, state, info, custom_bone_to_world);

  // visuals
  visuals.on_draw_model_execute(context, state, info, custom_bone_to_world);

  // call original function
  original(thisptr, context, state, info, custom_bone_to_world);

  // restore materials after we are done
  csgo::model_render->force_override_material(nullptr);

  CODE_END(STR("error handler - draw model execute - hooks"))
}

void hooks::render_view::hooked(void *thisptr, c_view_setup &view_setup,
                                c_view_setup &hud_setup, int clear_flags,
                                int what_to_draw) {

  CODE_START

  // visuals
  visuals.on_render_view(view_setup, hud_setup, clear_flags, what_to_draw);

  // call original function
  original(thisptr, view_setup, hud_setup, clear_flags, what_to_draw);

  CODE_END(STR("error gandler - render view - hooks"))
}
