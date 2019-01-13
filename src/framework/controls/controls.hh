//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include <vector>
#include "utils/color.hh"

// struct || todo: this will probably be useless when we have more controls that needs to use some of those variables
struct control_data {

    bool dragging;
    bool dropdown_opened;
};

namespace ruvi {

    void groupbox(int x, int y, int width, int height, std::string name);
    bool checkbox(int x, int y, bool &variable, std::string name);
    float slider(int x, int y, float min, float max, float &variable, std::string name);
    int combobox(int x, int y, std::vector<std::string> items, int& variable, std::string name);
}