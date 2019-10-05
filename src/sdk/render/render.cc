//
//  ruvi base
//

// includes
#include "render.hh"
#include "core/interfaces/interfaces.hh"

void draw::on_entry_point() {

  // initialize render manager
  fgui::render.create_font = draw::create_font;
  fgui::render.get_screen_size = draw::get_screen_size;
  fgui::render.get_text_size = draw::get_text_size;
  fgui::render.clip_rect = draw::clip_rect;
  fgui::render.rect = draw::rect;
  fgui::render.gradient = draw::gradient;
  fgui::render.colored_gradient = draw::colored_gradient;
  fgui::render.outline = draw::outline;
  fgui::render.line = draw::line;
  fgui::render.polygon = draw::polygon;
  fgui::render.circle = draw::circle;
  fgui::render.rounded_rect = draw::rounded_rect;
  fgui::render.text = draw::text;
  fgui::render.alpha = draw::alpha;

  // other fonts (esp, watermark, etc)
  fonts.emplace_back(FONT_VERDANA);
  fonts.emplace_back(FONT_ARIAL);
  fonts.emplace_back(FONT_TAHOMA);

  fgui::render.create_font(fonts[FONT_VERDANA], "Verdana", 11,
                           fgui::external::font_flags::SHADOW, false);
  fgui::render.create_font(fonts[FONT_ARIAL], "Arial", 11,
                           fgui::external::font_flags::SHADOW, false);
  fgui::render.create_font(fonts[FONT_TAHOMA], "fs Tahoma 8px", 13,
                           fgui::external::font_flags::SHADOW, false);
}

void draw::create_font(fgui::font &font, const std::string_view family,
                       int size, int flags, bool bold) {

  font = csgo::vgui_surface->create_font();
  csgo::vgui_surface->set_font_glyph_set(font, family.data(), size,
                                         bold ? 800 : 0, 0, 0, flags);
}

fgui::dimension draw::get_text_size(const fgui::font &font,
                                    const std::string_view text) {

  fgui::dimension temp = {0, 0};

  csgo::vgui_surface->get_text_size(
      font, std::wstring(text.begin(), text.end()).data(), temp.width,
      temp.height);

  return temp;
}

void draw::clip_rect(int x, int y, int width, int height) {

  fgui::rect viewport = {x, y, (x + width), (y + height)};

  csgo::vgui_surface->set_clip_rect(viewport.left, viewport.top, viewport.right,
                                    viewport.bottom);
}

bool draw::world_to_screen(vector3d &origin, vector3d &screen) {
  return (csgo::debug_overlay->screen_position(origin, screen) != 1);
}

void draw::rect(int x, int y, int w, int h, fgui::color color) {

  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_filled_rect(x, y, x + w, y + h);
}

void draw::gradient(int x, int y, int w, int h, int alpha1, int alpha2,
                    fgui::color color, bool horizontal) {

  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_filled_rect_fade(x, y, x + w, y + h, alpha1, alpha2,
                                            horizontal);
}

void draw::colored_gradient(int x, int y, int w, int h, fgui::color color1,
                            fgui::color color2, bool is_horizontal) {

  if (is_horizontal) { // horizontal

    draw::rect(x, y, w, h, color1);

    unsigned char first = color2.m_red;
    unsigned char second = color2.m_green;
    unsigned char third = color2.m_blue;

    for (int i = 0; i < w; i++) {
      float fi = i, fw = w;
      float a = fi / fw;
      unsigned int ia = a * 255;
      draw::rect(x + i, y, 1, h, fgui::color(first, second, third, ia));
    }
  }

  else { // vertical

    draw::rect(x, y, w, h, color1);

    unsigned char first = color2.m_red;
    unsigned char second = color2.m_green;
    unsigned char third = color2.m_blue;

    for (int i = 0; i < h; i++) {

      float fi = i, fh = h;
      float a = fi / fh;
      unsigned int ia = a * 255;
      draw::rect(x, y + i, w, 1, fgui::color(first, second, third, ia));
    }
  }
}

void draw::outline(int x, int y, int w, int h, fgui::color color) {

  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_outlined_rect(x, y, x + w, y + h);
}

void draw::line(int x, int y, int x2, int y2, fgui::color color) {

  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_line(x, y, x2, y2);
}

void draw::text(int x, int y, fgui::color color, unsigned long font,
                std::string_view text) {

  csgo::vgui_surface->draw_colored_text(font, x, y, color.m_red, color.m_green,
                                        color.m_blue, color.m_alpha,
                                        text.data());
}

void draw::get_screen_size(int &width, int &height) {

  csgo::vgui_surface->get_screen_size(width, height);
}

void draw::polygon(int count, fgui::vertex *vertex, fgui::color color) {

  static int texture = csgo::vgui_surface->create_new_texture_id(true);
  unsigned char buffer[4] = {255, 255, 255, 255};

  csgo::vgui_surface->draw_set_texture_rgba(texture, buffer, 1, 1);
  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_set_texture(texture);

  csgo::vgui_surface->draw_textured_polygon(count, vertex);
}

void draw::circle(int x, int y, int radius, int segments, fgui::color color) {

  csgo::vgui_surface->draw_set_color(color.m_red, color.m_green, color.m_blue,
                                     color.m_alpha);
  csgo::vgui_surface->draw_outlined_circle(x, y, radius, segments);
}

void draw::rounded_rect(int x, int y, int w, int h, int radius,
                        fgui::color color) {

  fgui::vertex round[64];

  for (std::size_t i = 0; i < 4; i++) {

    int new_x = x + ((i < 2) ? (w - radius) : radius);
    int new_y = y + ((i % 3) ? (h - radius) : radius);

    float a = 90.f * i;

    for (std::size_t j = 0; j < 16; j++) {

      float alpha = DEG2RAD(a + j * 6.f);

      round[(i * 16) + j] = fgui::vertex(fgui::precision_point(
          new_x + radius * sin(alpha), new_y - radius * cos(alpha)));
    }
  }

  draw::polygon(64, round, color);
}

void draw::texture(const std::string_view texture_name, int x, int y, int w,
                   int h) {

  static unsigned int texture_id = 0;

  bool initialized = [&]() {
    texture_id = csgo::vgui_surface->create_new_texture_id(true);

    // if somehow the texture id is invalid
    if (!texture_id)
      return false;

    csgo::vgui_surface->draw_set_texture_file(texture_id, texture_name.data(),
                                              1, false);

    return true;
  }();

  if (initialized) {

    static bool draw_once = [&]() {
      if (!csgo::vgui_surface->is_texture_id_valid(texture_id))
        return false;

      csgo::vgui_surface->draw_set_color(255, 255, 255, 255);
      csgo::vgui_surface->draw_set_texture(texture_id);

      return true;
    }();

    csgo::vgui_surface->draw_textured_rect(x, y, x + w, y + h);
  };
}

void draw::alpha(int x, int y, int w, int h) {

  for (std::size_t i = 0; i < h / 5; i++) {

    for (std::size_t t = 0; t < w / 5; t++) {

      int pixel_nr = roundf(t);
      int line_nr = roundf(i);
      bool start_with_light = line_nr % 2;
      bool is_brick_light = start_with_light ? pixel_nr % 2 : pixel_nr % 2 == 0;

      fgui::color new_color =
          is_brick_light ? fgui::color(60, 60, 60) : fgui::color(40, 40, 40);

      draw::rect(x + t * 5, y + i * 5, 5, 5, new_color);
    }
  }
};

void draw::outlets(int x, int y, int w, int h) { // laggy as fuck

  for (std::size_t i = 1; i < w; i++) {

    if (i % 4 == 0) {

      for (std::size_t t = 1; t < h; t++) {

        if (t % 4 == 0)
          draw::rect(x + i - 2, y + t - 5, 1, 3, fgui::color(15, 15, 15));
      }
    }

    if (i % 4 == 2) {

      for (std::size_t t = 1; t < h; t++) {

        if (t % 4 == 0)
          draw::rect(x + i - 2, y + t - 3, 1, 3, fgui::color(15, 15, 15));
      }
    }
  }
}
