#if defined(__has_include)
#  if __has_include(<ncurses.h>)
#    include <ncurses.h>
#    define COMBAT_USE_CURSES 1
#  elif __has_include(<curses.h>)
#    include <curses.h>
#    define COMBAT_USE_CURSES 1
#  else
#    include <stdio.h>
#    define printw printf
#    define scanw scanf
#    define refresh() ((void)0)
#  endif
#else
#  include <ncurses.h>
#  define COMBAT_USE_CURSES 1
#endif
#include <stdlib.h>
#include <time.h>
#include "./enemies.h"
#include "./items.h"
#include "./player.h"
#include "./combat.h"

void apply_damage(Stats *target_stats, int incoming_raw_dmg, int shield_hp_bonus) {
    int after_defense = incoming_raw_dmg - target_stats->defn;
    if (after_defense < 0) after_defense = 0;

    int final_damage = after_defense - shield_hp_bonus;
    if (final_damage < 0) final_damage = 0;

    target_stats->hp -= final_damage;
    if (target_stats->hp < 0) target_stats->hp = 0;
}

void handle_status_ticks(Stats *target_stats, StatusEffect active_effects[]) {
    for (int i = 0; i < 4; i++) {
        if (active_effects[i].status & POISON) {
            target_stats->hp -= active_effects[i].severity; 
            if (target_stats->hp < 0) target_stats->hp = 0;
            printw("Poison tick! Target takes %d damage. Current HP: %d\n", 
                    active_effects[i].severity, target_stats->hp);
            refresh();
        }
    }
}

void executeMove(Move move, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[]) {
    // Apply stat changes to attacker
    for (int i = 0; i < 4; i++) {
        if (move.statChanges[i].statName != NO_STAT) {
            switch (move.statChanges[i].statName) {
                case ATCK:
                    attacker_stats->atck += move.statChanges[i].delta;
                    break;
                case DEFN:
                    attacker_stats->defn += move.statChanges[i].delta;
                    break;
                case AGLT:
                    attacker_stats->aglt += move.statChanges[i].delta;
                    break;
                default:
                    break;
            }
        }
    }

    // Apply damage if aggressive
    if (move.moveType == AGGRESSIVE) {
        int damage = move.base + attacker_stats->atck;
        // Simple damage application, assuming no defense for now
        target_stats->hp -= damage;
        if (target_stats->hp < 0) target_stats->hp = 0;
        printw("Dealt %d damage!\n", damage);
        refresh();
    }

    // Apply status effects
    for (int i = 0; i < 2; i++) {
        if (move.afflictions[i].status != NO_STATUS) {
            // Find empty slot or overwrite
            for (int j = 0; j < 4; j++) {
                if (target_afflictions[j].status == NO_STATUS) {
                    target_afflictions[j] = move.afflictions[i];
                    break;
                }
            }
        }
    }
}

void startCombat(Player *player, Enemy *enemy) {
    printw("Combat starts! %s vs %s\n", player->name, enemy->name);
    refresh();
    srand(time(NULL));

    while (player->stats.hp > 0 && enemy->stats.hp > 0) {
        // Player turn
        printw("\nYour HP: %d/%d\n", player->stats.hp, player->stats.max_hp);
        printw("Enemy HP: %d/%d\n", enemy->stats.hp, enemy->stats.max_hp);
        printw("Choose your move (0-%d): ", player->noOfMoves - 1);
        refresh();
        int choice;
        scanw("%d", &choice); // this needs to change to whatever function will be used for choices
        if (choice < 0 || choice >= player->noOfMoves) {
            printw("Invalid choice.\n");
            refresh();
            continue;
        }
        executeMove(player->moves[choice], &player->stats, &enemy->stats, enemy->afflictions);
        handle_status_ticks(&enemy->stats, enemy->afflictions);
        if (enemy->stats.hp <= 0) {
            printw("You win!\n");
            refresh();
            break;
        }

        // Enemy turn
        int enemy_move = rand() % enemy->noOfMoves;
        printw("\n%s uses move %d\n", enemy->name, enemy_move);
        refresh();
        executeMove(enemy->moves[enemy_move], &enemy->stats, &player->stats, player->afflictions);
        handle_status_ticks(&player->stats, player->afflictions);
        if (player->stats.hp <= 0) {
            printw("You lose!\n");
            refresh();
            break;
        }
    }
}

int main() {
#ifdef COMBAT_USE_CURSES
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
#endif

    runCombat();

#ifdef COMBAT_USE_CURSES
    endwin();
#endif
    return 0;
}