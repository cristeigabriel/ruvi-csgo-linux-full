//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include "utils/color.hh"

// structs
struct geometry {

    int x;
    int y;
    int width;
    int height;
};

struct window_data {

    int selected_tab;
    bool dropdown_opened;
};

struct tab_data {

    tab_data(std::string tab_name, int tab_id) {

        name = tab_name;
        id = tab_id;
    }

    int id;
    std::string name;
};

namespace ruvi {

    void on_paint();
    void populate_geometry();
}