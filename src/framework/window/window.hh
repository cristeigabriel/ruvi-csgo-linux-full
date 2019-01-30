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
    bool is_opened;
};

namespace ruvi {

    void set_key_code_state();
    void on_paint();
    void populate_geometry();
}