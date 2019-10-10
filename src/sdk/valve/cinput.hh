///
///  ruvi base
///

// includes
#include "../vector/vector.hh"

#pragma once

class c_input {
public:
	char pad0[0xB4];
	bool camera_intercepting_mouse;
	bool camera_in_third_person;
	bool camera_moving_with_mouse;
	vector3d camera_offset;
	bool camera_distance_move;
	int camera_old_x;
	int camera_old_y;
	int camera_x;
	int camera_y;
	bool camera_is_ortographic;
};