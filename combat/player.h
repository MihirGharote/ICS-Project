#pragma once

#include "./combatAbstracts/moves.h"
#include "./combatAbstracts/stats.h"
#include "./items.h"
#include "./enemies.h"

typedef struct {
    char name[64];
    Stats stats;
    Weapon equipped_weapon;
    StatusEffect afflictions[4];
    Item inventory[10]; // Simple inventory
    int inventory_count;
    int wisdom_level; // For damage/defense calculations
} Player;

Player createPlayer();
char *runCombat(void);