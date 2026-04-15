#include <stdio.h>
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
            printf("Poison tick! Target takes %d damage. Current HP: %d\n", 
                    active_effects[i].severity, target_stats->hp);
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
        printf("Dealt %d damage!\n", damage);
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
    printf("Combat starts! %s vs %s\n", player->name, enemy->name);
    srand(time(NULL));

    while (player->stats.hp > 0 && enemy->stats.hp > 0) {
        // Player turn
        printf("\nYour HP: %d/%d\n", player->stats.hp, player->stats.max_hp);
        printf("Enemy HP: %d/%d\n", enemy->stats.hp, enemy->stats.max_hp);
        printf("Choose your move (0-%d): ", player->noOfMoves - 1);
        int choice;
        scanf("%d", &choice); // this needs to change to hatever function which will be used for choices
        if (choice < 0 || choice >= player->noOfMoves) {
            printf("Invalid choice.\n");
            continue;
        }
        executeMove(player->moves[choice], &player->stats, &enemy->stats, enemy->afflictions);
        handle_status_ticks(&enemy->stats, enemy->afflictions);
        if (enemy->stats.hp <= 0) {
            printf("You win!\n");
            break;
        }

        // Enemy turn
        int enemy_move = rand() % enemy->noOfMoves;
        printf("\n%s uses move %d\n", enemy->name, enemy_move);
        executeMove(enemy->moves[enemy_move], &enemy->stats, &player->stats, player->afflictions);
        handle_status_ticks(&player->stats, player->afflictions);
        if (player->stats.hp <= 0) {
            printf("You lose!\n");
            break;
        }
    }
}

int main() {
    runCombat();
    return 0;
}