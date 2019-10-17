//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"
#include "../vector/matrix3x4.hh"
#include "../vector/vector.hh"
#include <algorithm>

struct entity_t;

enum contents_t {
  CONTENTS_EMPTY    = 0,
  CONTENTS_SOLID    = 0x1,
  CONTENTS_WINDOW   = 0x2,
  CONTENTS_GRATE    = 0x8,
  CONTENTS_MOVEABLE = 0x4000,
  CONTENTS_DEBRIS   = 0x4000000,
  CONTENTS_MONSTER  = 0x2000000,
  CONTENTS_HITBOX   = 0x40000000
};

enum mask_shot_t {
  MASK_ALL = 0xFFFFFFFF,
  MASK_SHOT_BRUSHONLY =
      (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_DEBRIS),
  MASK_SHOT      = (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER |
               CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX),
  MASK_SOLID     = (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW |
                CONTENTS_MONSTER | CONTENTS_GRATE),
  MASK_SHOT_HULL = (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER |
                    CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE)
};

enum trace_type_t {
  TRACE_EVERYTHING = 0,
  TRACE_WORLD_ONLY,
  TRACE_ENTITIES_ONLY,
  TRACE_EVERYTHING_FILTER_PROPS,
};

struct cplane_t {
  vector3d      normal;
  float         dist;
  unsigned char type;
  unsigned char signbits;
  unsigned char pad[2];
};

struct csurface_t {
  const char *   name;
  short          surface_props;
  unsigned short flags;
};

struct trace_t {
  vector3d       start_position;
  vector3d       end_position;
  cplane_t       plane;
  float          fraction;
  int            contents;
  unsigned int   displacement_flags;
  bool           all_solid;
  bool           start_solid;
  float          fraction_left_solid;
  csurface_t     surface;
  int            hit_group;
  short          physicsbone;
  unsigned short world_surface_index;
  entity_t *     entity;
  int            hitbox;
};

struct ray_t {

  vector_aligned start;
  vector_aligned delta;
  vector_aligned start_offset;
  vector_aligned extents;

  const matrix3x4_t *world_axis_transform;

  bool is_ray;
  bool is_swept;

  ray_t() : world_axis_transform(nullptr) {}

  void init(vector3d _start, vector3d _end) {
    delta     = (_end - _start);
    is_swept  = (delta.length() != 0);
    extents.x = extents.y = extents.z = 0.0f;
    world_axis_transform              = nullptr;
    is_ray                            = true;
    start_offset.x = start_offset.y = start_offset.z = 0.0f;
    start                                            = _start;
  }
};

class i_trace_filter {
public:
  virtual bool should_hit_entity(entity_t *entity, int contents_mask) = 0;
  virtual trace_type_t get_trace_type() const                         = 0;
};

class c_trace_filter : public i_trace_filter {

public:
  bool should_hit_entity(entity_t *entity, int contents_mask) {
    return !(entity == p_skip);
  }

  virtual trace_type_t get_trace_type() const {
    return trace_type_t::TRACE_EVERYTHING;
  }

  void *p_skip;
};

class i_engine_trace {
public:
  int get_point_contents(const vector3d &vector_abs_position,
                         int             contents_mask = mask_shot_t::MASK_ALL,
                         entity_t **     ppentity      = nullptr) {
    return memory::vfunc<1, int>(this, std::ref(vector_abs_position),
                                 contents_mask, ppentity);
  }

  void clip_ray_to_entity(const ray_t &ray, unsigned int mask, entity_t *entity,
                          trace_t *trace) {
    return memory::vfunc<3, void>(this, std::ref(ray), mask, entity, trace);
  }

  void trace_ray(const ray_t &ray, unsigned int mask,
                 i_trace_filter *trace_filter, trace_t *trace) {
    return memory::vfunc<5, void>(this, std::ref(ray), mask, trace_filter,
                                  trace);
  }
};