//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"

class c_client_class;

struct screen_fade_t {
  float alpha;
};

enum client_frame_stage_t {

  FRAME_UNDEFINED = -1,
  FRAME_START,
  FRAME_NET_UPDATE_START,
  FRAME_NET_UPDATE_POSTDATAUPDATE_START,
  FRAME_NET_UPDATE_POSTDATAUPDATE_END,
  FRAME_NET_UPDATE_END,
  FRAME_RENDER_START,
  FRAME_RENDER_END
};

enum cstrike15_user_message_t {
  CS_UM_VGUIMenu = 1,
  CS_UM_Geiger = 2,
  CS_UM_Train = 3,
  CS_UM_HudText = 4,
  CS_UM_SayText = 5,
  CS_UM_SayText2 = 6,
  CS_UM_TextMsg = 7,
  CS_UM_HudMsg = 8,
  CS_UM_ResetHud = 9,
  CS_UM_GameTitle = 10,
  CS_UM_Shake = 12,
  CS_UM_Fade = 13, // Fade HUD in/out
  CS_UM_Rumble = 14,
  CS_UM_CloseCaption = 15,
  CS_UM_CloseCaptionDirect = 16,
  CS_UM_SendAudio = 17,
  CS_UM_RawAudio = 18,
  CS_UM_VoiceMask = 19,
  CS_UM_RequestState = 20,
  CS_UM_Damage = 21,
  CS_UM_RadioText = 22,
  CS_UM_HintText = 23,
  CS_UM_KeyHintText = 24,
  CS_UM_ProcessSpottedEntityUpdate = 25,
  CS_UM_ReloadEffect = 26,
  CS_UM_AdjustMoney = 27,
  CS_UM_UpdateTeamMoney = 28,
  CS_UM_StopSpectatorMode = 29,
  CS_UM_KillCam = 30,
  CS_UM_DesiredTimescale = 31,
  CS_UM_CurrentTimescale = 32,
  CS_UM_AchievementEvent = 33,
  CS_UM_MatchEndConditions = 34,
  CS_UM_DisconnectToLobby = 35,
  CS_UM_PlayerStatsUpdate = 36,
  CS_UM_DisplayInventory = 37,
  CS_UM_WarmupHasEnded = 38,
  CS_UM_ClientInfo = 39,
  CS_UM_XRankGet = 40, // Get ELO Rank Value from Client
  CS_UM_XRankUpd = 41, // Update ELO Rank Value on Client
  CS_UM_CallVoteFailed = 45,
  CS_UM_VoteStart = 46,
  CS_UM_VotePass = 47,
  CS_UM_VoteFailed = 48,
  CS_UM_VoteSetup = 49,
  CS_UM_ServerRankRevealAll = 50,
  CS_UM_SendLastKillerDamageToClient = 51,
  CS_UM_ServerRankUpdate = 52,
  CS_UM_ItemPickup = 53,
  CS_UM_ShowMenu = 54, // Show hud menu
  CS_UM_BarTime = 55,  // For the C4 progress bar.
  CS_UM_AmmoDenied = 56,
  CS_UM_MarkAchievement = 57,
  CS_UM_MatchStatsUpdate = 58,
  CS_UM_ItemDrop = 59,
  CS_UM_GlowPropTurnOff = 60,
  CS_UM_SendPlayerItemDrops = 61
};

class i_base_client_dll {
public:
  c_client_class *get_all_classes() {
    return memory::vfunc<8, c_client_class *>(this);
  }

  void view_fade(screen_fade_t *screen_fade) {
    return memory::vfunc<29, void>(this, screen_fade);
  }

  bool dispatch_user_message(int msg_type, unsigned int arg1,
                             unsigned int length, const void *data = nullptr) {
    return memory::vfunc<38, bool>(this, msg_type, arg1, length, data);
  }
};