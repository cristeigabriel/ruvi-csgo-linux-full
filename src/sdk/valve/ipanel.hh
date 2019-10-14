//
//  ruvi base
//

// includes
#include "sdk/memory/memory.hh"

class i_panel {
public:
  const std::string_view get_name(unsigned long long vgui_panel) {
    return memory::vfunc<37, const std::string_view>(this, vgui_panel);
  }
};
