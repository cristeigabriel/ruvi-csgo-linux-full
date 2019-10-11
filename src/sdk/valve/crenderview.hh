//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"

class c_render_view {
public:

	void set_blend(float alpha) {
		return memory::vfunc<4, void>(this, alpha);
	}

	void set_color_modulation(float const* color) {
		return memory::vfunc<6, void>(this, color);
	}
};