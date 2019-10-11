//
//  ruvi base
//

#pragma once

// includes
#include "core/interfaces/interfaces.hh"
#include "sdk/utils/vmthook.hh"
#include "sdk/valve/cmodelinfo.hh"
#include "sdk/vector/matrix3x4.hh"

namespace hooks {

void on_entry_point();

struct paint {
  typedef void(fn)(void *, paint_mode_t);
  static fn  hooked;
  static fn *original;
};

struct in_key_event {
  typedef int(fn)(void *, int, int, const char *);
  static fn  hooked;
  static fn *original;
};

struct lock_cursor {
  typedef void(fn)(void *);
  static fn  hooked;
  static fn *original;
};

struct create_move {
  typedef bool(fn)(void *, float, c_user_cmd *);
  static fn  hooked;
  static fn *original;
};

struct frame_stage_notify {
  typedef void(fn)(void *, client_frame_stage_t);
  static fn  hooked;
  static fn *original;
};

struct override_view {
  typedef void(fn)(void *, c_view_setup *);
  static fn  hooked;
  static fn *original;
};

struct draw_model_execute {
  typedef void(fn)(void *, i_mat_render_context *, void *, const model_render_info_t &, matrix3x4_t *);
  static fn  hooked;
  static fn *original;
};
} // namespace hooks