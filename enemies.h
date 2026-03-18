#pragma once

#include "combatAbstracts/moves.h"
#include "combatAbstracts/stats.h"

typedef struct {
    char name[64];
    char desc[256];
    Stats stats;
    unsigned short noOfMoves;
    Move moves[4];
    StatusEffect afflictions[4]; // Current Status Effects
} Enemy;

int getEnemyDamage(Enemy enemy, unsigned short move);


extern Enemy enemies[2];