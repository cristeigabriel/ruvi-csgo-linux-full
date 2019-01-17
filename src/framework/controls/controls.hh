//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include <vector>
#include <functional>
#include "utils/color.hh"

namespace ruvi {

    void groupbox(int x, int y, int width, int height, std::string name);
    bool checkbox(int x, int y, bool &variable, std::string name);
    float slider(int x, int y, float min, float max, float &variable, std::string name);
    int combobox(int x, int y, std::vector<std::string> items, int& variable, std::string name);
    bool button(int x, int y, std::function<void()> function, std::string name);
    void color_picker(int x, int y, Color& color, std::string name);
    void tab(int x, int y, int width, int height, std::vector<std::string> tabs, int& tab_id);
}