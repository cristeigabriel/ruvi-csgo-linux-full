//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "window.hh"
#include "utils/rendering.hh"
#include "framework/input/input.hh"
#include "framework/controls/controls.hh"

// declarations
geometry g;
window_data wd;
std::vector<tab_data> tabs;

bool boolean1;
bool boolean2;
float float1;

void ruvi::on_paint() {

    // initialize the geometry struct
    g.x = 100;
    g.y = 100;
    g.width = 650;
    g.height = 470;

    // tabs
    static bool do_once = [&]() {

        tabs.emplace_back(tab_data("Aimbot", 0));
        tabs.emplace_back(tab_data("Visuals", 1));
        tabs.emplace_back(tab_data("Misc", 2));
        tabs.emplace_back(tab_data("Skins", 3));

        return false;
    }();

    // populate geometry
    ruvi::populate_geometry();

    // controls
    if (wd.selected_tab == 0) {
        ruvi::groupbox(g.x + 20, g.y + 45, 250, 400, "groupbox1");
        ruvi::checkbox(g.x + 30, g.y + 45 + (15 * 1), boolean1, "checkbox1");

        if (boolean1)
            ruvi::checkbox(g.x + 40, g.y + 45 + (15 * 2), boolean2, "checkbox2");

        if (boolean1)
            ruvi::slider(g.x + 30, g.y + 45 + (15 * 3), 0.f, 255.f, float1, "slider1");
        else
            ruvi::slider(g.x + 30, g.y + 45 + (15 * 2), 0.f, 255.f, float1, "slider1");
    }

    else if (wd.selected_tab == 1)
        ruvi::groupbox(g.x + 20, g.y + 45, 250, 400, "groupbox2");

    else if (wd.selected_tab == 2)
        ruvi::groupbox(g.x + 20, g.y + 45, 250, 400, "groupbox3");

    else if (wd.selected_tab == 3)
        ruvi::groupbox(g.x + 20, g.y + 45, 250, 400, "groupbox4");
}

void ruvi::populate_geometry() {

    // window
    draw::outline(g.x - 1, g.y - 1, g.width + 2, g.height + 2, Color(60, 60, 60));
    draw::clear(g.x, g.y, g.width, g.height, Color(15, 15, 15));
    draw::outline(g.x + 6, g.y + 26, g.width - 12, g.height - 32, Color(60, 60, 60));
    draw::clear(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(35, 35, 35));

    // sandwich button
    if (input::is_mouse_in_region(g.x + 10, g.y + 6, 13, 13)) {
        draw::clear(g.x + 10, g.y + 6, 13, 1, Color(245, 245, 245));
        draw::clear(g.x + 10, g.y + 10, 13, 1, Color(245, 245, 245));
        draw::clear(g.x + 10, g.y + 14, 13, 1, Color(245, 245, 245));
    }

    else {
        draw::clear(g.x + 10, g.y + 6, 13, 1, Color(200, 200, 200));
        draw::clear(g.x + 10, g.y + 10, 13, 1, Color(200, 200, 200));
        draw::clear(g.x + 10, g.y + 14, 13, 1, Color(200, 200, 200));
    }

    // if we click on the tab button
    if (input::is_mouse_in_region(g.x + 10, g.y + 6, 13, 13)) {

        if (input::get_key_state(MOUSE_LEFT))
            wd.dropdown_opened = !wd.dropdown_opened;
    }

    if (wd.dropdown_opened) {

        draw::clear(g.x + 5, g.y + 25, 200, 200, Color(15, 15, 15));

        for (int i = 0; i < tabs.size(); i++) {

            auto tab_text_size = draw::get_text_size(fonts::menu, tabs[i].name);

            rect tab_area = {g.x + 10, g.y + 30 + (16 * i), (int)tab_text_size.x, 16};

            if (input::is_mouse_in_region(tab_area.left, tab_area.top, tab_area.right, tab_area.bottom))
                draw::text(tab_area.left, tab_area.top, Color(245, 245, 245), fonts::menu, tabs[i].name);
            else
                draw::text(tab_area.left, tab_area.top, Color(200, 200, 200), fonts::menu, tabs[i].name);

            if (input::is_mouse_in_region(tab_area.left, tab_area.top, tab_area.right, tab_area.bottom) && input::get_key_state(MOUSE_LEFT))
                wd.selected_tab = tabs[i].id;
        }
    }
}
