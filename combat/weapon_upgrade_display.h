#ifndef WEAPON_UPGRADE_DISPLAY_H
#define WEAPON_UPGRADE_DISPLAY_H

#include "./items.h"


void check_weapon_evolution(int slot_id,
                            int wisdom_level,
                            Weapon *current_weapon);

void check_all_weapon_upgrades(int wisdom_level,
                                Weapon weapon_slots[]);

void check_shield_upgrade(int wisdom_level,
                            Armor *current_shield);


#endif
