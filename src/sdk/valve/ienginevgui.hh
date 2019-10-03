//
//  ruvi base
//

#pragma once

enum vgui_panel_t {

  PANEL_ROOT = 0,
  PANEL_GAMEUIDLL,
  PANEL_CLIENTDLL,
  PANEL_TOOLS,
  PANEL_INGAMESCREENS,
  PANEL_GAMEDLL,
  PANEL_CLIENTDLL_TOOLS
};

enum paint_mode_t {

  PAINT_UIPANELS = (1 << 0),
  PAINT_INGAMEPANELS = (1 << 1),
  PAINT_CURSOR = (1 << 2),
};

class i_engine_vgui {
public:
};