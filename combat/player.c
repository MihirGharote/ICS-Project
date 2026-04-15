#if defined(__has_include)
#  if __has_include(<ncurses.h>)
#    include <ncurses.h>
#  elif __has_include(<curses.h>)
#    include <curses.h>
#  else
#    include <stdio.h>
#    define printw printf
#    define scanw scanf
#    define refresh() ((void)0)
#  endif
#else
#  include <ncurses.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./enemies.h"
#include "./items.h"
#include "./player.h"
#include "./combat.h"

Player createPlayer(int weapon_slot) {
    Player player = {
        "Hero",
        {5, 4, 6, 100, 100}, 
        get_evolved_weapon(weapon_slot, 1), // wisdom_level=1
        { {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0} },
        {item_antidote()}, // inventory
        1, // inventory count
        1 // wisdom level (starts at 1)
    };
    return player;
}

void runCombat(int weapon_slot) {
    Player player = createPlayer(weapon_slot);
    Enemy enemy = enemies[0];
    enemy.equipped_weapon = weapon_gada(); // Initialize enemy weapon
    startCombat(&player, &enemy);
}