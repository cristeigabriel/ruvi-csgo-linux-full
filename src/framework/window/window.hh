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

namespace ruvi {

    void on_paint();
    void populate_geometry();
}