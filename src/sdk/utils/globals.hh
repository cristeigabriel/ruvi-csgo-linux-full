///
///  ruvi base
///

#pragma once

// includes
#include "../vector/matrix3x4.hh"
#include "../vector/vector.hh"

class i_texture;

namespace globals {

inline bool        send_packet;
inline vector3d    last_angle;
inline matrix3x4_t bone_matrix[128];
inline i_texture* mirror_texture;
} // namespace globals