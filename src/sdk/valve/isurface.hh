//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/netvars/netvars.hh"
#include <functional>

// framework includes
#include <FGUI/dependencies/definitions.hh>

class i_surface {
public:
  OFFSET_PTR(bool, m_bClippingEnabled, 0x3A8);

  void draw_set_color(int red, int green, int blue, int alpha) {
    return memory::vfunc<14, void>(this, red, green, blue, alpha);
  }

  void draw_filled_rect(int x, int y, int width, int height) {
    return memory::vfunc<16, void>(this, x, y, width, height);
  }

  void draw_outlined_rect(int x, int y, int width, int height) {
    return memory::vfunc<18, void>(this, x, y, width, height);
  }

  void draw_line(int x1, int y1, int x2, int y2) {
    return memory::vfunc<19, void>(this, x1, y1, x2, y2);
  }

  void draw_set_texture_file(int texture_id, const std::string_view texture_name,
                             int hardware_filter, bool force_reload = 0) {
    return memory::vfunc<36, void>(this, texture_id, texture_name.data(),
                                   hardware_filter, force_reload);
  }

  void draw_set_texture_rgba(int texture_id, unsigned const char *rgba_data,
                             int width, int height) {
    return memory::vfunc<37, void>(this, texture_id, rgba_data, width, height);
  }

  void draw_set_texture(int texture_id) {
    return memory::vfunc<38, void>(this, texture_id);
  }

  void draw_textured_rect(int x, int y, int width, int height) {
    return memory::vfunc<41, void>(this, x, y, width, height);
  }

  bool is_texture_id_valid(int texture_id) {
    return memory::vfunc<42, bool>(this, texture_id);
  }

  int create_new_texture_id(bool is_procedural) {
    return memory::vfunc<43, int>(this, is_procedural);
  }

  void get_screen_size(int &width, int &height) {
    return memory::vfunc<44, void>(this, std::ref(width), std::ref(height));
  }

  void unlock_cursor() { return memory::vfunc<66, void>(this); }

  unsigned long create_font() { return memory::vfunc<71, unsigned long>(this); }

  bool set_font_glyph_set(unsigned long font, const std::string_view font_name, int tall,
                          int weight, int blur, int scanlines, int flags,
                          int min_range = 0, int max_range = 0) {
    return memory::vfunc<72, bool>(this, font, font_name.data(), tall, weight, blur,
                                   scanlines, flags, min_range, max_range);
  }

  void get_text_size(unsigned long font, const std::wstring_view text, int &wide,
                     int &tall) {
    return memory::vfunc<79, void>(this, font, text.data(), std::ref(wide),
                                   std::ref(tall));
  }

  void play_sound(const std::string_view file_name) {
    return memory::vfunc<82, void>(this, file_name.data());
  }

  void surface_get_cursor_pos(int &x, int &y) {
    return memory::vfunc<100, void>(this, std::ref(x), std::ref(y));
  }

  void draw_outlined_circle(int x, int y, int radius, int segments) {
    return memory::vfunc<103, void>(this, x, y, radius, segments);
  }

  void draw_textured_polygon(int vertex_count, fgui::vertex *vertex,
                             bool clip_vertices = true) {
    return memory::vfunc<106, void>(this, vertex_count, vertex, clip_vertices);
  }

  void draw_filled_rect_fade(int x, int y, int w, int h, unsigned int alpha1,
                             unsigned int alpha2, bool is_horizontal) {
    return memory::vfunc<123, void>(this, x, y, w, h, alpha1, alpha2,
                                    is_horizontal);
  }

  void get_clip_rect(int &x, int &y, int &w, int &h) {
    return memory::vfunc<146, void>(this, x, y, w, h);
  }

  void set_clip_rect(int x, int y, int w, int h) {
    return memory::vfunc<147, void>(this, x, y, w, h);
  }

  void disable_clipping(int state) {
    return memory::vfunc<159, void>(this, state);
  }

  void draw_colored_text(unsigned long font, int x, int y, int red, int green,
                         int blue, int alpha, const std::string_view text) {
    return memory::vfunc<163, void>(this, font, x, y, red, green, blue, alpha,
                                    text.data());
  }
};