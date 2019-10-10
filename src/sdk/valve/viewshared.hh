///
///  ruvi base
///

#pragma once

// includes
#include "../vector/vector.hh"

enum clear_flags_t {
  VIEW_CLEAR_COLOR        = 0x1,
  VIEW_CLEAR_DEPTH        = 0x2,
  VIEW_CLEAR_FULL_TARGET  = 0x4,
  VIEW_NO_DRAW            = 0x8,
  VIEW_CLEAR_OBEY_STENCIL = 0x10,
  VIEW_CLEAR_STENCIL      = 0x20,
};

enum motio_blur_mode_t {
  MOTION_BLUR_DISABLE = 1,
  MOTION_BLUR_GAME    = 2,
  MOTION_BLUR_SFM     = 3
};

class c_view_setup {
public:
  int               x;
  int               old_x;
  int               y;
  int               old_y;
  int               width;
  int               old_width;
  int               height;
  int               old_height;
  char              pad0[0x98];
  float             fov;
  float             fov_viewmodel;
  vector3d          origin;
  vector3d          angles;
  float             z_near;
  float             z_far;
  float             z_near_viewmodel;
  float             z_far_viewmodel;
  float             aspect_ratio;
  float             near_blur_depth;
  float             near_focus_depth;
  float             far_focus_depth;
  float             far_blur_depth;
  float             near_blur_radius;
  float             far_blur_radius;
  float             dof_quality;
  motio_blur_mode_t motion_blur_mode;
  float             shutter_time;
  vector3d          shutter_open_position;
  qangle            shutter_open_angles;
  vector3d          shutter_close_position;
  qangle            shutter_closeAngles;
  float             off_center_top;
  float             off_center_bottom;
  float             off_center_left;
  float             off_center_right;
  bool              off_center;
  bool              render_to_subrect_of_larger_screen;
  bool              do_bloom_and_tone_mapping;
  bool              do_depth_of_field;
  bool              hdr_target;
  bool              draw_world_normal;
  bool              cull_front_faces;
  bool              cache_full_scene_state;
  bool              render_flashlight_depth_translucents;
};