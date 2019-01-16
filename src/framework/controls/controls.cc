//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "controls.hh"
#include "framework/render/render.hh"
#include "framework/input/input.hh"

void ruvi::groupbox(int x, int y, int width, int height, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    draw::line(x - 1, y - 1, (x - 1) + 14, y + 2, Color(25, 25, 25));
    draw::line(x, y, x + 10, y, Color(60, 60, 60));
    draw::line((x - 1) + 15 + title_size.x + 5, y - 1, (x - 1) + width + 2, y - 1, Color(25, 25, 25));
    draw::line(x + 15 + title_size.x + 5, y, x + width, y, Color(60, 60, 60));
    draw::line(x - 1, y - 1, x - 1, (y - 1) + height + 2, Color(25, 25, 25));
    draw::line(x, y, x, y + height, Color(50, 50, 50));
    draw::line((x - 1), (y + 1) + height, (x - 1) + width + 2, (y + 1) + height, Color(25, 25, 25));
    draw::line(x, y + height, x + width, y + height, Color(60, 60, 60));
    draw::line((x - 1) + width + 2, y + 1, (x - 1) + width + 2, (y + 1) + height, Color(25, 25, 25));
    draw::line(x + width, y, x + width, y + height, Color(60, 60, 60));
    draw::clear(x + 1, y + 1, width - 1, height - 1, Color(15, 15, 15));
    draw::text(x + 15, y - 10 + (title_size.y / 2), Color(200, 200, 200), fonts::menu, name);
}

bool ruvi::checkbox(int x, int y, bool& variable, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    draw::clear(x - 1, y - 1, (10 + 2), (10 + 2), Color(60, 60, 60));
    draw::clear(x, y, 10, 10, Color(35, 35, 35));

    draw::text(x + 20, y + (10 / 2) - (title_size.y / 2), Color(200, 200, 200), fonts::menu, name);

    // if the checkbox is checked :^)
    if (variable)
        draw::clear(x + 1, y + 1, (10 - 2), (10 - 2), Color(245, 245, 245));

    if (input::is_mouse_in_region(x, y, 10, 10)) {

        if (input::get_key_press(MOUSE_LEFT))
            variable = !variable;
    }

    return variable;
}

float ruvi::slider(int x, int y, float min, float max, float& variable, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    auto value_size = draw::get_text_size(fonts::menu, std::to_string((int)variable));

    draw::clear(x - 1, y - 1, (150 + 2), (10 + 2), Color(60, 60, 60));
    draw::clear(x, y, 150, 10, Color(35, 35, 35));

    draw::text(x + 160, y + (10 / 2) - (title_size.y / 2), Color(200, 200, 200), fonts::menu, name);

    // slider value text
    draw::text(x + (150 / 2) - (value_size.x / 2), y + (10 + 2), Color(200, 200, 200), fonts::menu, std::to_string((int)variable));

    // calculate the ratio
    float ratio = variable / ( max - min );
    float location = (ratio * 150);

    draw::clear(x + 1, y + 1, (location - 2), (10 - 2), Color(200, 200, 200));

    // status
    bool dragging = false;

    // enable the dragging status
    if (input::is_mouse_in_region(x, y, 150, 10)) {

        if (input::get_key_state(MOUSE_LEFT))
            dragging = true;
    }

    // if the user is dragging the slider
    if ( dragging ) {

        if (input::get_key_state(MOUSE_LEFT)) {

            float new_x;
            float ratio;

            new_x = id.cursor.x - x - 1.f;

            if (new_x <= min)
                new_x = min;

            if (new_x >= 150)
                new_x = 150;

            ratio = (new_x / 150);

            variable = min + (max - min) * ratio;
        }

        else
            dragging = false;
    }

    return variable;
}


int ruvi::combobox(int x, int y, std::vector<std::string> items, int& variable, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    auto selected_item_size = draw::get_text_size(fonts::menu, items[variable]);

    draw::outline(x - 1, y - 1, (150 + 2), (15 + 2), Color(60, 60, 60));
    draw::clear(x, y, 150, 15, Color(35, 35, 35));

    draw::text(x + 160, y + (17 / 2) - (title_size.y / 2), Color(200, 200, 200), fonts::menu, name);

    // draw selected item
    draw::text(x + (150 / 2) - (selected_item_size.x / 2), y + (15 / 2) - (selected_item_size.y / 2), Color(200, 200, 200), fonts::menu, items[variable]);

    // status
    static bool is_opened = false;

    // open/close the dropdown list
    if (input::is_mouse_in_region(x, y, 150, 17)) {

        if (input::get_key_press(MOUSE_LEFT))
            is_opened = !is_opened;
    }

    if (is_opened) {

        draw::outline(x - 1, y + (18 - 1), (150 + 2), (16 * items.size()) + 2, Color(35, 35, 35));
        draw::clear(x, y + 18, 150, (16 * items.size()), Color(15, 15, 15));

        for (int i = 0; i < items.size(); i++) {

            if (input::is_mouse_in_region(x, y + 22 + (16 * i), 150, 16))
                draw::text(x + 5, y + 22 + (16 * i), Color(245, 245, 245), fonts::menu, items[i]);
            else
                draw::text(x + 5, y + 22 + (16 * i), Color(200, 200, 200), fonts::menu, items[i]);

            if (input::is_mouse_in_region(x, y + 22 + (16 * i), 150, 16)) {

                // select a item from the list
                if (input::get_key_state(MOUSE_LEFT))
                    variable = i;
            }
        }
    }

    return variable;
}

bool ruvi::button(int x, int y, std::function<void()> function, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    if (input::is_mouse_in_region(x, y, 150, 25)) {
        draw::outline(x - 1, y - 1, (150 + 2), (25 + 2), Color(50, 50, 50));
        draw::clear(x, y, 150, 25, Color(25, 25, 25));
        draw::text(x + (150 / 2) - (title_size.x / 2), y + (25 / 2) - (title_size.y / 2), Color(245, 245, 245), fonts::menu, name);
    }

    else {
        draw::outline(x - 1, y - 1, (150 + 2), (25 + 2), Color(60, 60, 60));
        draw::clear(x, y, 150, 25, Color(35, 35, 35));
        draw::text(x + (150 / 2) - (title_size.x / 2), y + (25 / 2) - (title_size.y / 2), Color(200, 200, 200), fonts::menu, name);
    }


    if (input::is_mouse_in_region(x, y, 150, 25)) {

        // call the function when the user clicks on the button area
        if (input::get_key_press(MOUSE_LEFT))
            function();
    }

    // if the function was successfully called, return true
    if (function)
        return true;

    return false;
}

void ruvi::colorpicker(int x, int y, Color& color, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    draw::outline(x - 1, y - 1, (15 + 2), (10 + 2), Color(60, 60, 60));
    draw::alpha_background(x, y, 15, 10);
    draw::clear(x, y, 15, 10, Color(color));
    draw::gradient(x, y, 15, 3, 200, 0, false, Color(0, 0, 0));

    draw::text(x + (15 + 5), y - 1, Color(200, 200, 200), fonts::menu, name);

    // status
    static bool is_opened = false;

    // open/close the color picker
    if (input::is_mouse_in_region(x, y, 15, 10)) {

        if (input::get_key_press(MOUSE_LEFT))
            is_opened = !is_opened;
    }

    if (is_opened) {

        int pixelation = 5;
        float new_width = 150;
        float new_height = 150;

        // background
        draw::outline(x - 1, y - new_height - 1, new_width + (45 + 2), new_height + 2, Color(60, 60, 60));
        draw::clear(x, y - new_height, new_width + 45, new_height, Color(35, 35, 35));
        draw::alpha_background(x, y - new_height, new_width, new_height);

        // pallet
        for (int py = 0; py < new_height; py += pixelation) {

            for (int px = 0; px < new_width; px += pixelation) {

                Color new_color = Color::hsb_to_rgb(Color::get_hue(color), px / new_width, py / new_height, color.a());

                draw::clear(x + px, y - py - 5, pixelation, pixelation, new_color);

                if (input::is_mouse_in_region(x + px, y - py - 5, pixelation, pixelation)) {

                    if (input::get_key_state(MOUSE_LEFT))
                        color = new_color;
                }
            }
        }

        // hue bar
        for (int px = 0; px < new_height; px += pixelation) {

            Color new_color = Color::hsb_to_rgb(px / 150.f, 1, 1);

            draw::clear(x + new_width + 5, y - new_height + px, 15, pixelation, new_color);

            if (input::is_mouse_in_region(x + new_width + 5, y - new_height + px, 15, pixelation)) {

                if (input::get_key_state(MOUSE_LEFT))
                    color = new_color;
            }
        }

        // alpha bar
        for (int px = 0; px < new_height; px += pixelation) {

            Color new_color = Color(color.r(), color.g(), color.b(), px / new_height * 255);

            draw::clear(x + new_width + 25, y - new_height + px, 15, pixelation, new_color);

            if (input::is_mouse_in_region(x + new_width + 25, y - new_height + px, 15, pixelation)) {

                if (input::get_key_state(MOUSE_LEFT))
                    color = new_color;
            }
        }
    }
}
