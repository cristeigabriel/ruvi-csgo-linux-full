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

// variables
bool boolean1;
bool boolean2;
bool boolean3;
float float1;
float float2;
int integer1;
int integer2;
int integer3;
void function1() {};
std::vector<std::string> vector1 = { "Item 0", "Item 1", "Item 2", "Item 3", "Item 4" };
Color color1 = Color( 100, 100, 245 );

void ruvi::set_key_code_state() {

    // switch
    g.is_opened = !g.is_opened;
}

void ruvi::on_paint() {

    if (g.is_opened) {

        // initialize the geometry struct
        g.x = 100;
        g.y = 100;
        g.width = 650;
        g.height = 470;

        // populate geometry
        ruvi::populate_geometry();

        // register tabs
        ruvi::tab(g.x + 5, g.y + 26, g.width - 10, 25, {"Aimbot", "Visuals", "Misc", "Skins"}, integer2);

        // controls
        if (integer2 == 0) {
            ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox1");
            ruvi::checkbox(g.x + 30, g.y + 70 + (15 * 1), boolean1, "checkbox1");

            if (boolean1)
                ruvi::checkbox(g.x + 30, g.y + 70 + (15 * 2), boolean2, "checkbox2");

            if (boolean1) {
                ruvi::slider(g.x + 30, g.y + 70 + (15 * 3), 0.f, 255.f, float1, "slider1");
                ruvi::slider(g.x + 30, g.y + 70 + (15 * 5), 0.f, 255.f, float2, "slider2");
            }

            else {
                ruvi::slider(g.x + 30, g.y + 70 + (15 * 2), 0.f, 255.f, float1, "slider1");
                ruvi::slider(g.x + 30, g.y + 70 + (15 * 4), 0.f, 255.f, float2, "slider2");
            }
        }

        else if (integer2 == 1) {
            ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox2");
            ruvi::combobox(g.x + 30, g.y + 70 + (15 * 1), vector1, integer1, "combobox1");
            ruvi::checkbox(g.x + 30, g.y + 70 + (20 * 2), boolean3, "checkbox3");
            ruvi::button(g.x + 30, g.y + 70 + (20 * 3), function1, "button1");
        }

        else if (integer2 == 2) {
            ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "groupbox3");
            ruvi::color_picker(g.x + 30, g.y + 70 + (15 * 1), color1, "colorpicker1");
        }

        else if (integer2 == 3) {
            ruvi::groupbox(g.x + 20, g.y + 70, 250, 350, "");
            ruvi::tab(g.x + 20, g.y + 70 - 1, 250 + 1, 25, {"Tab1", "Tab2"}, integer3);
        }
    }
}

void ruvi::populate_geometry() {

    // window
    draw::outline(g.x - 1, g.y - 1, g.width + 2, g.height + 2, Color(60, 60, 60));
    draw::clear(g.x, g.y, g.width, g.height, Color(15, 15, 15));
    draw::outline(g.x + 6, g.y + 26, g.width - 12, g.height - 32, Color(60, 60, 60));
    draw::clear(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(35, 35, 35));
    draw::outline(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(45, 45, 45));
    draw::text(g.x + 5, g.y + 5, Color(200, 200, 200), fonts::menu, "Ruvi Framework");
}
