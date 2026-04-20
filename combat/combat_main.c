#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "./enemies.h"
#include "./items.h"
#include "./player.h"
#include "../renderer/renderCombat.h"
#include "../choice_handling/choice_system.h"
#include "../globals.h"

extern int dmg_base_values[];

void apply_damage(Stats *target_stats, int incoming_raw_dmg, int shield_hp_bonus) {
    int after_defense = incoming_raw_dmg - target_stats->defn;
    if (after_defense < 0) after_defense = 0;

    int final_damage = after_defense - shield_hp_bonus;
    if (final_damage < 0) final_damage = 0;

    target_stats->hp -= final_damage;
    if (target_stats->hp < 0) target_stats->hp = 0;
}

char* handle_status_ticks(Stats *target_stats, StatusEffect active_effects[]) {
    static char status_msg[256];
    int msg_pos = 0;
    for (int i = 0; i < 4; i++) {
        if (active_effects[i].status & POISON) {
            target_stats->hp -= active_effects[i].severity; 
            if (target_stats->hp < 0) target_stats->hp = 0;
            msg_pos += snprintf(status_msg + msg_pos, sizeof(status_msg) - msg_pos, "Poison tick! Target takes %d damage. Current HP: %d\n", 
                    active_effects[i].severity, target_stats->hp);
        }
    }
    return status_msg;
}

int executeMove(Move move, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[]) {
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
        return damage;
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
    return 0;
}

char* executeWeaponMove(Weapon weapon, int dmg_type_index, Stats *attacker_stats, Stats *target_stats, StatusEffect target_afflictions[], int attacker_wisdom) {
    static char message[256];
    // Calculate damage for this specific move type
    int damage = calculate_move_type_damage(weapon, dmg_type_index, attacker_wisdom, 1.0f);
    
    // Apply defense
    int final_damage = damage - target_stats->defn;
    if (final_damage < 0) final_damage = 0;
    
    target_stats->hp -= final_damage;
    if (target_stats->hp < 0) target_stats->hp = 0;
    
    // Poison damage type special handling
    if (dmg_type_index == 11) { // DMG_POISON
        for (int j = 0; j < 4; j++) {
            if (target_afflictions[j].status == NO_STATUS) {
                target_afflictions[j].status = POISON;
                target_afflictions[j].severity = 2;
                break;
            }
        }
        strcpy(message, "Dealt ");
        char dmg_str[10];
        sprintf(dmg_str, "%d", final_damage);
        strcat(message, dmg_str);
        strcat(message, " damage with ");
        strcat(message, weapon.name);
        strcat(message, "! Poison applied!");
    } else {
        strcpy(message, "Dealt ");
        char dmg_str[10];
        sprintf(dmg_str, "%d", final_damage);
        strcat(message, dmg_str);
        strcat(message, " damage with ");
        strcat(message, weapon.name);
        strcat(message, "!");
    }
    return message;
}

// Combat interface funcns
Weapon* get_player_current_weapon() {
    return &player.equipped_weapon;
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

int get_player_available_moves(int* out_move_indices, int max_count) {
    return get_available_move_types(player.equipped_weapon, out_move_indices, max_count);
}

char** get_all_move_type_names(void) {
    static char* move_names[] = {"PUNCH", "SLASH", "WHACKING", "STAB", "THROW", 
                                        "FRONTKICK", "AXEKICK", "SIDEKICK", "FIRE", 
                                        "LIGHTNING", "SHOOT", "POISON"};
    return move_names;
}

char* execute_player_choice_move(Enemy *enemy, int move_type_index) {
    char* message = executeWeaponMove(player.equipped_weapon, move_type_index, &player.stats, 
                      &enemy->stats, enemy->afflictions, player.wisdom_level);
    int damage_dealt = calculate_move_type_damage(player.equipped_weapon, move_type_index, player.wisdom_level, 1.0f) - enemy->stats.defn;
    if (damage_dealt < 0) damage_dealt = 0;
    player.wisdom_level += calculate_wisdom_increase(damage_dealt);
    return message;
}

int get_enemy_random_move(Enemy *enemy) {
    int enemy_move_types[12];
    int enemy_move_count = get_available_move_types(enemy->equipped_weapon, enemy_move_types, 12);
    
    if (enemy_move_count > 0) {
        return enemy_move_types[rand() % enemy_move_count];
    }
    return 0;
}

char* execute_enemy_choice_move(Enemy *enemy, int move_type_index) {
    return executeWeaponMove(enemy->equipped_weapon, move_type_index, &enemy->stats, 
                      &player.stats, player.afflictions, enemy->wisdom_level);
}

char* startCombat(Enemy *enemy) {
    initialize_enemy_weapons();  // Ensure enemy weapons are initialized
    static char combat_log[16384];
    strcpy(combat_log, "Combat starts! ");
    strcat(combat_log, player.name);
    strcat(combat_log, " vs ");
    strcat(combat_log, enemy->name);
    strcat(combat_log, "\n");
    strcat(combat_log, enemy->name);
    strcat(combat_log, " uses: ");
    strcat(combat_log, enemy->equipped_weapon.name);
    strcat(combat_log, "\n");
    
    srand(time(NULL));
    flash();

    while (player.stats.hp > 0 && enemy->stats.hp > 0) {
        #ifndef RUNCOMBAT
        renderCombat(enemy);
        #endif
        // Player turn
        strcat(combat_log, "\n========== PLAYER TURN ==========\n");
        char hp_str[50];
        sprintf(hp_str, "Your HP: %d/%d\n", player.stats.hp, player.stats.max_hp);
        strcat(combat_log, hp_str);
        sprintf(hp_str, "Enemy HP: %d/%d\n", enemy->stats.hp, enemy->stats.max_hp);
        strcat(combat_log, hp_str);
        strcat(combat_log, "Equipped: ");
        strcat(combat_log, player.equipped_weapon.name);
        strcat(combat_log, "\n");
        
        // Get available move types
        int move_types[12];
        int move_count = get_player_available_moves(move_types, 12);
        
        if (move_count == 0) {
            strcat(combat_log, "No available moves!\n");
            break;
        }

        char **moveNames = (char **)malloc(12 * sizeof(char *));
        for (int i = 0; i < move_count; i++) {
            moveNames[i] = get_all_move_type_names()[move_types[i]];
        }
        #ifndef RUNCOMBAT
        int selected_move_type = move_types[get_menu_choice(choicewin, moveNames, move_count) - 1];
        #else
        int selected_move_type = move_types[0];
        #endif
        free(moveNames);        

        char* player_msg = execute_player_choice_move(enemy, selected_move_type);
        #ifndef RUNCOMBAT
        renderPlayerAttack(player_msg, enemy);
        #endif
        strcat(combat_log, player_msg);
        strcat(combat_log, "\n");
        
        char* status_msg = handle_status_ticks(&enemy->stats, enemy->afflictions);
        if (strlen(status_msg) > 0) {
            //renderEnemyAttack(status_msg, enemy);
            strcat(combat_log, status_msg);
        }
        
        if (enemy->stats.hp <= 0) {
            strcat(combat_log, "You win!\n");
            break;
        }

        // Enemy turn
        strcat(combat_log, "\n========== ENEMY TURN ==========\n");
        int enemy_move_types[12];
        int enemy_move_count = get_available_move_types(enemy->equipped_weapon, enemy_move_types, 12);
        
        if (enemy_move_count > 0) {
            int enemy_choice = rand() % enemy_move_count;
            int enemy_selected_move = enemy_move_types[enemy_choice];
            char move_str[50];
            sprintf(move_str, "%s uses %s!\n", enemy->name, get_move_type_name(enemy_selected_move));
            strcat(combat_log, move_str);
            char* enemy_msg = execute_enemy_choice_move(enemy, enemy_selected_move);
            #ifndef RUNCOMBAT
            renderEnemyAttack(enemy_msg, enemy);
            #endif
            strcat(combat_log, enemy_msg);
            strcat(combat_log, "\n");
        }
        
        char* player_status_msg = handle_status_ticks(&player.stats, player.afflictions);
        if (strlen(player_status_msg) > 0) {
            strcat(combat_log, player_status_msg);
        }
        if (player.stats.hp <= 0) {
            strcat(combat_log, "You lose!\n");
            break;
        }
    }
    return combat_log;
}

#ifdef RUNCOMBAT
int main() {
    createPlayer();
    player.equipped_weapon = weapon_bow();
    printf("%s", startCombat(&enemies[0]));
    return 0;
}
#endif
