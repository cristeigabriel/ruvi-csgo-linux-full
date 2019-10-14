//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/matrix3x4.hh"
#include "sdk/vector/vector.hh"
#include <string_view>

struct model_t;
class i_material;

typedef float quaternion[4];
typedef float radian_euler[3];

struct mstudiobone_t {

  int name_index;

  inline const std::string_view name() const {
    return (char *)(this) + name_index;
  }

  int          parent;
  int          bone_controller[6];
  vector3d     position;
  quaternion   q_quaternion;
  radian_euler rotation;
  vector3d     position_scale;
  vector3d     rotation_scale;
  matrix3x4_t  pose_to_bone;
  quaternion   alignment;
  int          flags;
  int          proc_type;
  int          proc_index;

  mutable int physics_bone;

  inline void *procedure() const {

    if (proc_index == 0)
      return nullptr;
    else
      return (void *)((unsigned char *)(this) + proc_index);
  };

  int surface_prop_index;

  inline const std::string_view surface_prop_name() const {
    return (char *)(this) + surface_prop_index;
  }

  inline int get_surface_prop(void) const { return surface_prop_lookup; }

  int contents;
  int surface_prop_lookup;
  int pad0[0x7];
};

struct mstudiobbox_t {

  int      bone;
  int      group;
  vector3d bbmin;
  vector3d bbmax;
  int      hitbox_index;
  int      pad0[0x3];
  float    m_flRadius;
  int      pad1[0x4];

  const char *get_name() {

    if (!hitbox_index) return nullptr;

    return (const char *)((unsigned char *)this + hitbox_index);
  }
};

struct mstudiohitboxset_t {

  int name_index;

  inline char *const name() const { return ((char *)this) + name_index; }

  int number_of_hitboxes;
  int hitbox_index;

  inline mstudiobbox_t *hitbox(std::size_t index) const {
    return reinterpret_cast<mstudiobbox_t *>(((unsigned char *)this) +
                                             hitbox_index) +
           index;
  };
};

struct studiohdr_t {

  int      id;
  int      version;
  int      checksum;
  char     name[64];
  int      length;
  vector3d eye_position;
  vector3d illumination_position;
  vector3d hull_min;
  vector3d hull_max;
  vector3d view_bbmin;
  vector3d view_bbmax;
  int      flags;
  int      number_of_bones;
  int      bone_index;

  inline mstudiobone_t *bone(std::size_t index) const {

    assert(index >= 0 && index < number_of_bones);

    return reinterpret_cast<mstudiobone_t *>(((unsigned char *)this) +
                                             bone_index) +
           index;
  };

  int remap_bone_sequence(int sequence, int local_bone) const;
  int remap_bone_animation(int animation, int local_bone) const;

  int number_of_bone_controllers;
  int bone_controller_index;
  int number_of_hitbox_sets;
  int hitbox_set_index;

  mstudiohitboxset_t *hitbox_set(std::size_t index) const {
    (index >= 0 && index < number_of_hitbox_sets);
    return reinterpret_cast<mstudiohitboxset_t *>(((unsigned char *)this) +
                                                  hitbox_set_index) +
           index;
  };

  inline mstudiobbox_t *hitbox(std::size_t index, int set) const {

    const mstudiohitboxset_t *studio_hitbox_set = hitbox_set(set);

    if (!studio_hitbox_set) return nullptr;

    return studio_hitbox_set->hitbox(index);
  };

  inline int hitbox_count(int set) const {
    const mstudiohitboxset_t *studio_hitbox_set = hitbox_set(set);

    if (!studio_hitbox_set) return 0;

    return studio_hitbox_set->number_of_hitboxes;
  };
};

class c_model_info {
public:
  void *get_model(int index) { return memory::vfunc<2, void *>(this, index); }

  int get_model_index(const std::string_view file_name) {
    return memory::vfunc<3, int>(this, file_name.data());
  }

  const std::string_view get_model_name(const void *model_name) {
    return memory::vfunc<4, const std::string_view>(this, model_name);
  }

  void get_model_materials(const model_t *model, int count,
                           i_material **pp_material) {
    return memory::vfunc<18, void>(this, model, count, pp_material);
  }

  studiohdr_t *get_studio_model(const model_t *model) {
    return memory::vfunc<31, studiohdr_t *>(this, model);
  }
};