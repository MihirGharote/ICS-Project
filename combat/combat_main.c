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
#include "./combat_interface.h"

extern int dmg_base_values[];

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

int executeWeaponMove(Weapon weapon, int dmg_type_index, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[], int attacker_wisdom) {
    // Calculate damage for this specific move type
    int damage = calculate_move_type_damage(weapon, dmg_type_index, attacker_wisdom, 1.0f);
    
    // Apply defense
    int final_damage = damage - target_stats->defn;
    if (final_damage < 0) final_damage = 0;
    
    target_stats->hp -= final_damage;
    if (target_stats->hp < 0) target_stats->hp = 0;
    
    printw("Dealt %d damage with %s!\n", final_damage, weapon.name);
    refresh();
    
    // Poison damage type special handling
    if (dmg_type_index == 11) { // DMG_POISON
        for (int j = 0; j < 4; j++) {
            if (target_afflictions[j].status == NO_STATUS) {
                target_afflictions[j].status = POISON;
                target_afflictions[j].severity = 2;
                break;
            }
        }
        printw("Poison applied!\n");
        refresh();
    }
    
    return final_damage;
}

// Combat interface funcns
Weapon* get_player_current_weapon(Player *player) {
    return &player->equipped_weapon;
}

const char* get_move_type_name(int move_type_index) {
    const char* move_names[] = {"PUNCH", "SLASH", "WHACKING", "STAB", "THROW", 
                                 "FRONTKICK", "AXEKICK", "SIDEKICK", "FIRE", 
                                 "LIGHTNING", "SHOOT", "POISON"};
    if (move_type_index >= 0 && move_type_index < 12) {
        return move_names[move_type_index];
    }
    return "UNKNOWN";
}

int get_move_type_base_damage(int move_type_index) {
    if (move_type_index >= 0 && move_type_index < 12) {
        return dmg_base_values[move_type_index];
    }
    return 0;
}

int get_player_available_moves(Player *player, int* out_move_indices, int max_count) {
    return get_available_move_types(player->equipped_weapon, out_move_indices, max_count);
}

const char** get_all_move_type_names(void) {
    static const char* move_names[] = {"PUNCH", "SLASH", "WHACKING", "STAB", "THROW", 
                                        "FRONTKICK", "AXEKICK", "SIDEKICK", "FIRE", 
                                        "LIGHTNING", "SHOOT", "POISON"};
    return move_names;
}

int execute_player_choice_move(Player *player, Enemy *enemy, int move_type_index) {
    int damage_dealt = executeWeaponMove(player->equipped_weapon, move_type_index, &player->stats, 
                      &enemy->stats, enemy->afflictions, player->wisdom_level);
    player->wisdom_level += calculate_wisdom_increase(damage_dealt);
    return 1; // success
}

int get_enemy_random_move(Enemy *enemy) {
    int enemy_move_types[12];
    int enemy_move_count = get_available_move_types(enemy->equipped_weapon, enemy_move_types, 12);
    
    if (enemy_move_count > 0) {
        return enemy_move_types[rand() % enemy_move_count];
    }
    return 0;
}

void execute_enemy_choice_move(Enemy *enemy, Player *player, int move_type_index) {
    executeWeaponMove(enemy->equipped_weapon, move_type_index, &enemy->stats, 
                      &player->stats, player->afflictions, enemy->wisdom_level);
}

void startCombat(Player *player, Enemy *enemy) {
    char* move_names[] = {"PUNCH", "SLASH", "WHACKING", "STAB", "THROW", "FRONTKICK", "AXEKICK", "SIDEKICK", "FIRE", "LIGHTNING", "SHOOT", "POISON"};
    printw("Combat starts! %s vs %s\n", player->name, enemy->name);
    printw("%s uses: %s\n", enemy->name, enemy->equipped_weapon.name);
    refresh();
    srand(time(NULL));

    while (player->stats.hp > 0 && enemy->stats.hp > 0) {
        // Player turn
        printw("\n========== PLAYER TURN ==========\n");
        printw("Your HP: %d/%d\n", player->stats.hp, player->stats.max_hp);
        printw("Enemy HP: %d/%d\n", enemy->stats.hp, enemy->stats.max_hp);
        printw("Equipped: %s\n", player->equipped_weapon.name);
        
        // Get available move types
        int move_types[12];
        int move_count = get_available_move_types(player->equipped_weapon, move_types, 12);
        
        if (move_count == 0) {
            printw("No available moves!\n");
            refresh();
            break;
        }
        
        // Choice handled by teammate's code
        // int selected_move_type = teammate_get_player_choice(move_types, move_count);
        // For now, default to first move
        int selected_move_type = move_types[0];
        
        int damage_dealt = executeWeaponMove(player->equipped_weapon, selected_move_type, &player->stats, &enemy->stats, enemy->afflictions, player->wisdom_level);
        player->wisdom_level += calculate_wisdom_increase(damage_dealt);
        handle_status_ticks(&enemy->stats, enemy->afflictions);
        
        if (enemy->stats.hp <= 0) {
            printw("You win!\n");
            refresh();
            break;
        }

        // Enemy turn
        printw("\n========== ENEMY TURN ==========\n");
        int enemy_move_types[12];
        int enemy_move_count = get_available_move_types(enemy->equipped_weapon, enemy_move_types, 12);
        
        if (enemy_move_count > 0) {
            int enemy_choice = rand() % enemy_move_count;
            int enemy_selected_move = enemy_move_types[enemy_choice];
            printw("%s uses %s!\n", enemy->name, move_names[enemy_selected_move]);
            refresh();
            executeWeaponMove(enemy->equipped_weapon, enemy_selected_move, &enemy->stats, &player->stats, player->afflictions, enemy->wisdom_level);
        }
        
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