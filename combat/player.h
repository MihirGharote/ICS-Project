#pragma once

#include "./combatAbstracts/moves.h"
#include "./combatAbstracts/stats.h"
#include "./items.h"
#include "./enemies.h"

typedef struct {
    char name[64];
    Stats stats;
    unsigned short noOfMoves;
    Move moves[4];
    StatusEffect afflictions[4];
    Item inventory[10]; // Simple inventory
    int inventory_count;
} Player;

Player createPlayer();
void runCombat();