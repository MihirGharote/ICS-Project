#include <stdio.h>
#include <stdlib.h>

#include "./enemies.h"

int getEnemyDamage(Enemy enemy, unsigned short move) {
    if (move >= enemy.noOfMoves) {
        puts("Invalid move no.\n");
        exit(EXIT_FAILURE);
    }
    if (enemy.moves[move].moveType != AGGRESSIVE) {
        return 0;
    }
    int base = enemy.moves[move].base;
    int atck = enemy.stats.atck;
    return base + atck;
}

Enemy enemies[2] = {
    {
        "Goblin",
        "A glint of wickedness flashes in its crooked grin",
        {4, 5, 8},
        1,
        {{
            AGGRESSIVE,
            5,
            -20,
            {{NO_STAT, 0}},
            {{NO_STATUS, 0}}
        }},
        {{NO_STATUS, 0}}
    }
};
