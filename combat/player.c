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
        {5, 4, 6, 100, 100}, 
        get_evolved_weapon(0, 1), // wisdom_level=1 (intiially)
        { {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0} },
        {item_antidote()}, // inventory
        1, 
        1 
    };
    return player;
}

char *runCombat() {
    Player player = createPlayer();
    Enemy enemy = enemies[0];
    enemy.equipped_weapon = weapon_gada(); // Initialize enemy weapon
    return startCombat(&player, &enemy);
}