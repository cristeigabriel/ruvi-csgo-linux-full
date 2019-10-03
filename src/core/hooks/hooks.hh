//
//  ruvi base
//

#pragma once

// includes
#include "core/interfaces/interfaces.hh"
#include "sdk/utils/vmthook.hh"

namespace hooks {

void on_entry_point();

struct paint {
  typedef void(fn)(void *, paint_mode_t);
  static fn hooked;
  static fn *original;
};

struct in_key_event {
  typedef int(fn)(void *, int, int, const char *);
  static fn hooked;
  static fn *original;
};

struct lock_cursor {
  typedef void(fn)(void *);
  static fn hooked;
  static fn *original;
};

struct create_move {
  typedef bool(fn)(void *, float, c_user_cmd *);
  static fn hooked;
  static fn *original;
};

struct frame_stage_notify {
  typedef void(fn)(void *, client_frame_stage_t);
  static fn hooked;
  static fn *original;
};
} // namespace hooks