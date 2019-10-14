//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"

class i_material;

struct stencil_state_t {

  bool enable;
  int  fail;
  int  zfail;
  int  pass;
  int  compare;
  int  ref;
  int  mask1;
  int  mask2;
};

class i_texture {
public:
  int get_actual_width() { return memory::vfunc<3, int>(this); }

  int get_actual_height() { return memory::vfunc<4, int>(this); }
};

class i_mat_render_context {
public:

  int release() { return memory::vfunc<1, int>(this); }

  void set_render_target(i_texture *p_texture) {
    return memory::vfunc<6, void>(this, p_texture);
  }

  void draw_screen_space_rectangle(
      i_material *p_material, int dest_x, int dest_y, int width, int height,
      float src_texture_x1, float src_texture_y1, float src_texture_x2,
      float src_texture_y2, int src_texture_width, int src_texture_height,
      void *p_client_renderable = nullptr, int x_dice = 1, int y_dice = 1) {
    return memory::vfunc<113, void>(
        this, p_material, dest_x, dest_y, width, height, src_texture_x1,
        src_texture_y1, src_texture_x2, src_texture_y2, src_texture_width,
        src_texture_height, p_client_renderable, x_dice, y_dice);
  }

  void push_render_target_and_viewport() {
    return memory::vfunc<115, void>(this);
  }

  void pop_render_target_and_viewport() {
    return memory::vfunc<119, void>(this);
  }

  void set_stencil_state(stencil_state_t &state) {
    return memory::vfunc<127, void>(this, std::ref(state));
  }
};