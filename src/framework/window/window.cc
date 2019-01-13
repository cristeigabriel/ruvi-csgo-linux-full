//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "window.hh"
#include "utils/rendering.hh"
#include "framework/controls/controls.hh"

// declarations
geometry g;

void ruvi::on_paint() {

    // initialize the geometry struct
    g.x = 100;
    g.y = 100;
    g.width = 650;
    g.height = 470;

    // populate geometry
    ruvi::populate_geometry();

    // controls
    ruvi::groupbox(g.x + 20, g.y + 45, 250, 400, "groupbox");
}

void ruvi::populate_geometry() {

    // window
    draw::outline(g.x - 1, g.y - 1, g.width + 2, g.height + 2, Color(60, 60, 60));
    draw::clear(g.x, g.y, g.width, g.height, Color(15, 15, 15));
    draw::outline(g.x + 6, g.y + 26, g.width - 12, g.height - 32, Color(60, 60, 60));
    draw::clear(g.x + 5, g.y + 25, g.width - 10, g.height - 30, Color(35, 35, 35));

    // sandwich button
    draw::clear( g.x + 10, g.y + 6, 13, 1, Color(200, 200, 200));
    draw::clear( g.x + 10, g.y + 10, 13, 1, Color(200, 200, 200));
    draw::clear( g.x + 10, g.y + 14, 13, 1, Color(200, 200, 200));
}
