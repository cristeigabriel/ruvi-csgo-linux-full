//
//  ruvi base
//

// incldues
#include "sdk/vector/vector.hh"

class c_base_client_state {
public:
  char pad0[0x20C];
  unsigned int delta_tick;
  bool paused;
  char pad1[0x3];
  int view_entity;
  char pad2[0x8];
  char level_name[260];
  char level_name_short[40];
  char group_name[40];
  char pad3[0x34];
  unsigned int max_clients;
  char pad4[0x4984];
  float last_server_tick_time;
  bool in_simulation;
  char pad5[0x3];
  unsigned int old_tick_count;
  float tick_remainder;
  float frame_time;
  unsigned int last_out_going_command;
  unsigned int choked_commands;
  unsigned int last_command_ack;
  unsigned int command_ack;
  unsigned int sound_sequence;
  char pad6[0x50];
  qangle view_wangles;
};