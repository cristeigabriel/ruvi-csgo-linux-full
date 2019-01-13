//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "hooks.hh"
#include "utils/rendering.hh"
#include "framework/input/input.hh"
#include "framework/window/window.hh"

// declarations
static vmt_hook engine_vgui_hook;
static vmt_hook vgui_panel_hook;

// originals
hooks::paint::fn* hooks::paint::original;
hooks::paint_traverse::fn* hooks::paint_traverse::original;

void hooks::on_entry_point() {

    if ( engine_vgui_hook.initialize_and_hook_instance( csgo::engine_vgui ) )
        engine_vgui_hook.apply_hook<hooks::paint>( 15 );

    if ( vgui_panel_hook.initialize_and_hook_instance( csgo::vgui_panel ) )
        vgui_panel_hook.apply_hook<hooks::paint_traverse>( 42 );
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

        // draw stuff here
        draw::text(5, 5, Color(200, 200, 200), fonts::watermark, "Ruvi Framework");

        // menu
        ruvi::on_paint();

        finish_drawing( csgo::vgui_surface );
    }
}

auto hooks::paint_traverse::hooked( void* thisptr, unsigned long long vgui_panel, bool force_repaint, bool allow_force ) -> void {

    // call original function
    original( thisptr, vgui_panel, force_repaint, allow_force );
}