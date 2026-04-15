#if defined(__has_include)
#  if __has_include(<ncurses.h>)
#    include <ncurses.h>
#  elif __has_include(<curses.h>)
#    include <curses.h>
#  else
#    include <stdio.h>
#    define printw printf
#    define refresh() ((void)0)
#    define scanw scanf
#  endif
#else
#  include <ncurses.h>
#endif

#include <string.h>
#include "items.h"
#include "player.h"


/*
Displays all base weapons and lets player select one
Returns chosen weapon
*/

Weapon choose_weapon_screen()
{
    int choice = 0;

    printw("\nChoose your weapon before entering combat:\n\n");

    printw("1. Bare Hands\n");
    printw("2. Ancient Sword\n");
    printw("3. Wooden Mallet\n");
    printw("4. Iron Gada\n");
    printw("5. Short Bow\n");
    printw("6. Fiery Sword\n");
    printw("7. Dagger\n");

    printw("\nEnter choice: ");
    refresh();

    scanw("%d", &choice);

    switch(choice)
    {
        case 1: return weapon_bare_hands();
        case 2: return weapon_ancient_sword();
        case 3: return weapon_mallet();
        case 4: return weapon_gada();
        case 5: return weapon_bow();
        case 6: return weapon_fiery_sword();
        case 7: return weapon_shadow_dagger();
        default:
            printw("\nInvalid choice. Defaulting to Bare Hands.\n");
            refresh();
            return weapon_bare_hands();
    }
}
