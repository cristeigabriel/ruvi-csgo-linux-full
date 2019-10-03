//
//  ruvi base
//

#pragma once

// includes
#include <functional>
#include "../memory/memory.hh"
#include "../vector/vector.hh"

struct model_t;
class matrix3x4_t;

class i_client_renderable {
public:
  virtual ~i_client_renderable(){};

  model_t *get_model() { return memory::vfunc<8, model_t *>(this); }

  int draw_model(int flags, unsigned char alpha) {
    return memory::vfunc<9, int>(this, flags, alpha);
  }

  bool setup_bones(matrix3x4_t *bone_matrix, int max_bones, int bone_mask,
                   float curtime = 0) {
    return memory::vfunc<13, bool>(this, bone_matrix, max_bones, bone_mask,
                                   curtime);
  }

  void get_render_bounds(vector3d &mins, vector3d &maxs) {
    return memory::vfunc<17, void>(this, std::ref(mins), std::ref(maxs));
  }
};