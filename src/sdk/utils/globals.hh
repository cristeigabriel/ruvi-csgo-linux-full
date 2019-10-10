///
///  ruvi base
///

// includes
#include "../vector/vector.hh"
#include "../vector/matrix3x4.hh"

namespace globals {

inline bool        send_packet;
inline vector3d    last_angle;
inline matrix3x4_t bone_matrix[128];
} // namespace globals