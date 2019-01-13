//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "controls.hh"
#include "utils/rendering.hh"

void ruvi::groupbox(int x, int y, int width, int height, std::string name) {

    auto title_size = draw::get_text_size(fonts::menu, name);

    draw::line( x - 1, y - 1, ( x - 1 ) + 14, y + 2, Color( 25, 25, 25 ) );
    draw::line( x, y, x + 10, y, Color( 60, 60, 60 ) );
    draw::line( ( x - 1 ) + 15 + title_size.x + 5, y - 1, ( x - 1 ) + width + 2, y - 1, Color( 25, 25, 25 ) );
    draw::line( x + 15 + title_size.x + 5, y, x + width, y, Color( 60, 60, 60 ) );
    draw::line( x - 1, y - 1, x - 1, ( y - 1 ) + height + 2, Color( 25, 25, 25 ) );
    draw::line( x, y, x, y + height, Color( 50, 50, 50 ) );
    draw::line( ( x - 1 ), ( y + 1 ) + height, ( x - 1 ) + width + 2, ( y + 1 ) + height, Color( 25, 25, 25 ) );
    draw::line( x, y + height, x + width, y + height, Color( 60, 60, 60 ) );
    draw::line( ( x - 1 ) + width + 2, y + 1, ( x - 1 ) + width + 2, ( y + 1 ) + height, Color( 25, 25, 25 ) );
    draw::line( x + width, y, x + width, y + height, Color( 60, 60, 60 ) );
    draw::clear( x + 1, y + 1, width - 1, height - 1, Color( 15, 15, 15 ) );
    draw::text( x + 15, y - 10 + ( title_size.y / 2 ), Color( 200, 200, 200 ), fonts::menu, name );
}
