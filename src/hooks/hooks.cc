//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "hooks.hh"
#include "framework/render/render.hh"
#include "framework/input/input.hh"
#include "framework/window/window.hh"

// declarations
static vmt_hook engine_vgui_hook;
static vmt_hook vgui_panel_hook;
static vmt_hook input_internal_hook;

// originals
hooks::paint::fn* hooks::paint::original;
hooks::paint_traverse::fn* hooks::paint_traverse::original;
hooks::set_key_code_state::fn* hooks::set_key_code_state::original;

void hooks::on_entry_point() {

    if ( engine_vgui_hook.initialize_and_hook_instance( csgo::engine_vgui ) )
        engine_vgui_hook.apply_hook<hooks::paint>( 15 );

    if ( vgui_panel_hook.initialize_and_hook_instance( csgo::vgui_panel ) )
        vgui_panel_hook.apply_hook<hooks::paint_traverse>( 42 );

    if ( input_internal_hook.initialize_and_hook_instance( csgo::input_internal ) )
        input_internal_hook.apply_hook<hooks::set_key_code_state>( 92 );
}

auto hooks::paint::hooked( void* thisptr, e_paint_mode mode ) -> void {

    // call original function
    original( thisptr, mode );

    static auto start_drawing = reinterpret_cast<void ( * )( void* )>(memory::find_pattern( "vguimatsurface_client.so", "55 48 89 E5 53 48 89 FB 48 83 EC 28 80 3D" ));
    static auto finish_drawing = reinterpret_cast<void ( * )( void* )>(memory::find_pattern( "vguimatsurface_client.so", "55 31 FF 48 89 E5 53" ));

    if ( mode & PAINT_UIPANELS ) {

        start_drawing( csgo::vgui_surface );

        // input system
        input::on_paint();

        // watermark
        draw::text(5, 5, Color(200, 200, 200), fonts::watermark, "Ruvi");

        // menu
        ruvi::on_paint();

        finish_drawing( csgo::vgui_surface );
    }
}

auto hooks::paint_traverse::hooked( void* thisptr, unsigned long long vgui_panel, bool force_repaint, bool allow_force ) -> void {

    // call original function
    original( thisptr, vgui_panel, force_repaint, allow_force );
}

auto hooks::set_key_code_state::hooked( void* thisptr, e_button_code key, bool is_pressed ) -> void {

    if ( key == KEY_INSERT && is_pressed )
       ruvi::on_set_key_code_state();

    // call the original function
    original( thisptr, key, is_pressed );
}
