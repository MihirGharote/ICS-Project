#pragma once

#include "./player.h"

// Combat result structure for returning outcomes without printing
typedef struct {
    int damage_dealt;
    int success;  // 1 for success, 0 for failure
    char message[256];  // Description of what happened
} CombatResult;

void apply_damage(Stats *target_stats, int incoming_raw_dmg, int shield_hp_bonus);
char* handle_status_ticks(Stats *target_stats, StatusEffect active_effects[]);
void executeMove(Move move, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[]);
char* executeWeaponMove(Weapon weapon, int dmg_type_index, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[], int attacker_wisdom);
char* startCombat(Player *player, Enemy *enemy);
char* startCombat(Player *player, Enemy *enemy);