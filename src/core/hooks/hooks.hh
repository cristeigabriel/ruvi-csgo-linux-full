//
//  ruvi base
//

#pragma once

// includes
#include "core/interfaces/interfaces.hh"
#include "sdk/utils/vmthook.hh"
#include "sdk/valve/cmodelinfo.hh"
#include "sdk/vector/matrix3x4.hh"
#include <mutex>

namespace hooks {

void on_entry_point();

struct paint {
  using fn = void(void *, paint_mode_t);
  static fn  hooked;
  static fn *original;
};

struct in_key_event {
  using fn = int(void *, int, int, const std::string_view);
  static fn  hooked;
  static fn *original;
};

struct lock_cursor {
  using fn = void(void *);
  static fn  hooked;
  static fn *original;
};

struct create_move {
  using fn = bool(void *, float, c_user_cmd *);
  static fn  hooked;
  static fn *original;
};

struct frame_stage_notify {
  using fn = void(void *, client_frame_stage_t);
  static fn  hooked;
  static fn *original;
};

struct override_view {
  using fn = void(void *, c_view_setup *);
  static fn  hooked;
  static fn *original;
};

struct draw_model_execute {
  using fn = void(void *, i_mat_render_context *, void *,
                  const model_render_info_t &, matrix3x4_t *);
  static fn  hooked;
  static fn *original;
};

struct render_view {
  using fn = void(void *, c_view_setup &, c_view_setup &, int, int);
  static fn  hooked;
  static fn *original;
};

struct override_mouse_input {
  using fn = void(void *, float *x, float *y);

  static fn  hooked;
  static fn *original;
};
} // namespace hooks