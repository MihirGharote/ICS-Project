#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./enemies.h"
#include "./items.h"
#include "./player.h"
#include "./combat.h"

Player createPlayer() {
    Player player = {
        "Hero",
        {5, 4, 6, 100, 100}, // stats: atck, defn, aglt, hp, max_hp
        2,
        {{
            AGGRESSIVE,
            8,
            0,
            {{NO_STAT, 0}},
            {{NO_STATUS, 0}}
        },{
            AGGRESSIVE,
            6,
            0,
            {{NO_STAT, 0}},
            {{POISON, 2}}
        }},
        { {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0} },
        {item_antidote()}, // inventory
        1
    };
    return player;
}

void runCombat() {
    Player player = createPlayer();
    startCombat(&player, &enemies[0]);
}