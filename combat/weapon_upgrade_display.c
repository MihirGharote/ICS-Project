#include "weapon_upgrade_display.h"
#include "../globals.h"
#include "./items.h"
#include <ncurses.h>
#include <string.h>

#define TOTAL_WEAPON_SLOTS 6

static void dramatic_mvprintw(int y, int x, const char *text, int delay) {
    wmove(mainwin, y, x);
    for (int i = 0; text[i] != '\0'; i++) {
        waddch(mainwin, text[i]);
        refresh();
        napms(delay);
    }
}

static void show_weapon_upgrade(const char *old_name, const char *new_name) {
    dramatic_mvprintw(2, 2, "Your wisdom increases...", 20);
    napms(250);

    dramatic_mvprintw(3, 2, "Your weapon responds to your growth...", 25);
    napms(350);

    char oldWeaponText[64];
    sprintf(oldWeaponText, "Previous weapon: %s", old_name);
    dramatic_mvprintw(5, 2, oldWeaponText, 15);
    napms(250);

    char newWeaponText[64];
    sprintf(newWeaponText, "New weapon unlocked: %s", new_name);
    dramatic_mvprintw(7, 2, newWeaponText, 15);
    napms(350);

    dramatic_mvprintw(9, 2, "You feel its power flow through you.", 25);
}

static void show_shield_upgrade(const char *old_name, const char *new_name) {
    dramatic_mvprintw(2, 2, "Your defense strengthens...", 25);
    napms(300);

    dramatic_mvprintw(3, 2, "Your shield transforms...", 25);
    napms(350);

    char oldShieldText[64];
    sprintf(oldShieldText, "Previous shield: %s", old_name);
    dramatic_mvprintw(5, 2, oldShieldText, 15);
    napms(250);

    char newShieldText[64];
    sprintf(newShieldText, "New shield unlocked: %s", new_name);
    dramatic_mvprintw(7, 2, newShieldText, 15);
    napms(350);

    dramatic_mvprintw(9, 2, "Your protection has reached a new level.", 25);
}

void check_weapon_evolution(int slot_id, int wisdom_level,
                            Weapon *current_weapon) {
    Weapon evolved_weapon;

    evolved_weapon = get_evolved_weapon(slot_id, wisdom_level);

    if (strcmp(current_weapon->name, evolved_weapon.name) != 0) {
        show_weapon_upgrade(current_weapon->name, evolved_weapon.name);

        *current_weapon = evolved_weapon;
    }
}

void check_all_weapon_upgrades(int wisdom_level, Weapon weapon_slots[]) {
    for (int i = 0; i < TOTAL_WEAPON_SLOTS; i++) {
        check_weapon_evolution(i, wisdom_level, &weapon_slots[i]);
    }
}

void check_shield_upgrade(int wisdom_level, Armor *current_shield) {
    Armor evolved_shield;

    evolved_shield = get_evolved_shield(wisdom_level);

    if (strcmp(current_shield->name, evolved_shield.name) != 0) {
        show_shield_upgrade(current_shield->name, evolved_shield.name);

        *current_shield = evolved_shield;
    }
}
