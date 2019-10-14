//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/vector.hh"
#include <functional>

struct player_info_t {
  int64_t __pad0;
  union {
    int64_t xuid;
    struct {
      int xuid_low;
      int xuid_high;
    };
  };
  char          name[128];
  int           userid;
  char          guid[33];
  unsigned int  steam3_id;
  char          friendsname[128];
  bool          is_fake_player;
  bool          ishltv;
  unsigned int  customfiles[4];
  unsigned char filesdownloaded;
};

class i_engine_client {
public:
  void get_screen_size(int &width, int &height) {
    return memory::vfunc<5, void>(this, std::ref(width), std::ref(height));
  }

  bool get_player_info(int ent_num, player_info_t *info) {
    return memory::vfunc<8, bool>(this, ent_num, info);
  }

  int get_player_for_user_id(int user_id) {
    return memory::vfunc<9, int>(this, user_id);
  }

  int get_local_player() { return memory::vfunc<12, int>(this); }

  void get_view_angles(qangle *angles) {
    return memory::vfunc<18, void>(this, angles);
  }

  void set_view_angles(qangle *angles) {
    return memory::vfunc<19, void>(this, angles);
  }

  int get_max_clients() { return memory::vfunc<20, int>(this); }

  bool is_in_game() { return memory::vfunc<26, bool>(this); }

  bool is_connected() { return memory::vfunc<27, bool>(this); }

  const std::string_view get_map_name() {
    return memory::vfunc<52, const std::string_view>(this);
  }

  bool is_taking_screenshot() { return memory::vfunc<92, bool>(this); }

  void execute_client_cmd(const std::string_view command) {
    return memory::vfunc<108, void>(this, command.data());
  }

  void client_cmd_unrestricted(const std::string_view command) {
    return memory::vfunc<113, void>(this, command.data());
  }
};
