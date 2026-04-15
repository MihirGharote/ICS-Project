#pragma once

#include "./player.h"

void apply_damage(Stats *target_stats, int incoming_raw_dmg, int shield_hp_bonus);
void handle_status_ticks(Stats *target_stats, StatusEffect active_effects[]);
void executeMove(Move move, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[]);
int executeWeaponMove(Weapon weapon, int dmg_type_index, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[], int attacker_wisdom);
void startCombat(Player *player, Enemy *enemy);