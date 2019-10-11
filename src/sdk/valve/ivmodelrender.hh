//
//  ruvi base
//

#pragma once

// includes
#include "sdk/vector/vector.hh"
#include "sdk/memory/memory.hh"

class i_material;

struct model_render_info_t {

	vector3d origin;
	vector3d angles;
	char pad0[0x4];
	void* renderable;
	const model_t* model;
	const matrix3x4_t* model_to_world;
	const matrix3x4_t* lighting_offset;
	const vector3d* lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitbox_set;
	unsigned short instance;
};

class iv_model_render {
public:

	void force_override_material(i_material* material, int null1 = 0, int null2 = 0) {
		return memory::vfunc<1, void>( this, material, null1, null2 );
	}

	bool is_forced_material_override() {
		return memory::vfunc<2, bool>( this );
	}
};