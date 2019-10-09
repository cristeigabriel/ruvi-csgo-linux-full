//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/vector.hh"
#include <functional>

class iv_debug_overlay {
public:
  bool screen_position(const vector3d &in, vector3d &out) {
    return memory::vfunc<11, bool>(this, std::ref(in), std::ref(out));
  }
};