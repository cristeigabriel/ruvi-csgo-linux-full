//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"

enum analog_code_t {
  ANALOG_CODE_INVALID = -1,
  MOUSE_X             = 0,
  MOUSE_Y,
  MOUSE_XY, // invoked when either x or y changes
  MOUSE_WHEEL,
  ANALOG_CODE_LAST = 10,
};

class i_input_system {
public:
  bool is_button_down(int code) { return memory::vfunc<15, bool>(this, code); }

  int get_analog_value(analog_code_t code) {
    return memory::vfunc<18, int>(this, code);
  }

  int get_analog_delta(analog_code_t code) {
    return memory::vfunc<19, int>(this, code);
  }

  const char *button_code_to_string(int code) {
    return memory::vfunc<40, const char *>(this, code);
  }
};