//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "window.hh"
#include "framework/render/render.hh"
#include "framework/input/input.hh"
#include "framework/controls/controls.hh"

// declarations
geometry g;
window_data wd;
std::vector<tab_data> tabs;

bool boolean1;
bool boolean2;
bool boolean3;
float float1;
int integer1;
void function1() {};
std::vector<std::string> vector1 = { "Item 0", "Item 1", "Item 2", "Item 3", "Item 4" };

void ruvi::on_paint() {

    // initialize the geometry struct
    g.x = 100;
    g.y = 100;
    g.width = 650;
    g.height = 470;

    static bool do_once = [&]() {

        // register tabs
        tabs.emplace_back(tab_data("Aim-assistance", 0));
        tabs.emplace_back(tab_data("Visuals", 1));
        tabs.emplace_back(tab_data("Miscellaneous", 2));
        tabs.emplace_back(tab_data("Skin-changer", 3));

        return false;
    }();

    // populate geometry
    ruvi::populate_geometry();

    // controls
    if (wd.selected_tab == 0) {
        ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox1");
        ruvi::checkbox(g.x + 30, g.y + 70 + (15 * 1), boolean1, "checkbox1");

        if (boolean1)
            ruvi::checkbox(g.x + 30, g.y + 70 + (15 * 2), boolean2, "checkbox2");

        if (boolean1)
            ruvi::slider(g.x + 30, g.y + 70 + (15 * 3), 0.f, 255.f, float1, "slider1");
        else
            ruvi::slider(g.x + 30, g.y + 70 + (15 * 2), 0.f, 255.f, float1, "slider1");
    }

    else if (wd.selected_tab == 1) {
        ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox2");
        ruvi::combobox(g.x + 30, g.y + 70 + (15 * 1), vector1, integer1, "combobox1");
        ruvi::checkbox(g.x + 30, g.y + 70 + (20 * 2), boolean3, "checkbox3");
        ruvi::button(g.x + 30, g.y + 70 + (20 * 3), function1, "button1");
    }

    else if (wd.selected_tab == 2)
        ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox3");

    else if (wd.selected_tab == 3)
        ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox4");
}

void ruvi::populate_geometry() {

    // window
    draw::outline(g.x - 1, g.y - 1, g.width + 2, g.height + 2, Color(60, 60, 60));
    draw::clear(g.x, g.y, g.width, g.height, Color(15, 15, 15));
    draw::outline(g.x + 6, g.y + 26, g.width - 12, g.height - 32, Color(60, 60, 60));
    draw::clear(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(35, 35, 35));
    draw::outline(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(45, 45, 45));

    // tab panel
    draw::gradient(g.x + 5, g.y + (25 + 15), g.width - 10, 20, 200, 0, false, Color(0, 0, 0));
    draw::clear(g.x + 5, g.y + 25, g.width - 10, 25, Color(25, 25, 25));

    if (tabs.size() > 0) {

        int button_size = (g.width - 10) / tabs.size();

        for (int i = 0; i < tabs.size(); i++) {

            auto tab_title_size = draw::get_text_size(fonts::menu, tabs[i].name);

            rect tab_area = {g.x + 6 + (i * button_size), g.y + 25, button_size, 25};

            if (input::is_mouse_in_region(tab_area.left, tab_area.top, tab_area.right, tab_area.bottom)) {

                // if the user selects a new tab
                if (input::get_key_state(MOUSE_LEFT))
                    wd.selected_tab = tabs[i].id;
            }

            if (input::is_mouse_in_region(tab_area.left, tab_area.top, tab_area.right, tab_area.bottom))
                draw::text(tab_area.left + (tab_area.right / 2) - (tab_title_size.x / 2), tab_area.top + (tab_area.bottom / 2) - (tab_title_size.y / 2), Color(245, 245, 245), fonts::menu, tabs[i].name);
            else
                draw::text(tab_area.left + (tab_area.right / 2) - (tab_title_size.x / 2), tab_area.top + (tab_area.bottom / 2) - (tab_title_size.y / 2), Color(200, 200, 200), fonts::menu, tabs[i].name);
        }
    }

    // miscellaneous button
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
}
