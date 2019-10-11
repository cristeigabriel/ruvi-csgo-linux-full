///
///  ruvi base
///

// includes
#include "../vector/matrix3x4.hh"
#include "../vector/vector.hh"

namespace globals {

inline bool        send_packet;
inline vector3d    last_angle;
inline matrix3x4_t bone_matrix[128];
} // namespace globals