///
///  ruvi base
///

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/vector.hh"

class i_prediction {
public:

  void set_local_view_angle(vector3d &angle) {
    return memory::vfunc<14, void>(this, std::ref(angle));
  }
};