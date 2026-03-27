#pragma once

#include "./stats.h"
#include "./status.h"

enum MoveType { UNDEFINED_MOVE, AGGRESSIVE, DEFENSIVE, OTHER };

typedef struct {
    enum MoveType moveType;
    int base;  // Could be base attack, or base defense, or other,
               // depending on MoveType
    int manaDelta;
    StatChange statChanges[4];
    StatusEffect afflictions[2];
} Move;
