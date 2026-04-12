#include <stdio.h>
#include "./enemies.h"
#include "./items.h"

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

int main() {
    int dmg = getEnemyDamage(enemies[0], 1);
    printf("%s hits for %d damage!\n", enemies[0].name, dmg);
    Armor my_shield = armor_basic_shield();
    apply_damage(&enemies[0].stats, dmg, my_shield.defense_value);
    handle_status_ticks(&enemies[0].stats, enemies[0].afflictions);
    Item my_antidote = item_antidote();
    use_item(&my_antidote, &enemies[0].stats, enemies[0].afflictions);
    return 0;
}