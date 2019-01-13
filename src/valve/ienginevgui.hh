//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// namespace
namespace vgui {
	typedef unsigned int v_panel;
};

// enums
enum e_vgui_panel {

	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum e_paint_mode {

	PAINT_UIPANELS = ( 1 << 0 ),
	PAINT_INGAMEPANELS = ( 1 << 1 ),
	PAINT_CURSOR = ( 1 << 2 ),
};

class i_engine_vgui {
public:
};