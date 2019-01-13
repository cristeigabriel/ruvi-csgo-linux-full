//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include "utils/color.hh"

namespace ruvi {

    void groupbox(int x, int y, int width, int height, std::string name);
	bool checkbox(std::string name, bool *var, int x, int y);
}
