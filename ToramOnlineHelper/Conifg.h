#pragma once
#include <vector>
#include "Item.h"
#include "Player.h"

extern std::vector<CPlayer *> g_vecPlayers;
extern std::vector<CEquipment *> g_vecMainWeapons , g_vecSubWeapons , g_vecArmors , g_vecAdditionalEquips , g_vecSpecialEquips;
extern std::vector<CXtal *> g_vecGeneralXtals , g_vecWeaponXtals , g_vecArmorXtals , g_vecAdditionalXtals , g_vecSpecialXtals;

BOOL LoadDefaultConfig();