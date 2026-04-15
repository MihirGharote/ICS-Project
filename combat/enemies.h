#pragma once

#include "./combatAbstracts/moves.h"
#include "./combatAbstracts/stats.h"
#include "./items.h"

typedef struct {
    char name[64];
    char desc[256];
    Stats stats;
    Weapon equipped_weapon;
    StatusEffect afflictions[4]; // Current Status Effects
    int wisdom_level; // For damage/defense calculations
} Enemy;

int getEnemyDamage(Enemy enemy, unsigned short move);


extern Enemy enemies[1];
