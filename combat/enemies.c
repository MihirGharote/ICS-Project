#include <stdio.h>
#include <stdlib.h>
#include "./items.h"

#include "./enemies.h"

int getEnemyDamage(Enemy enemy, unsigned short move) {
    // This function is deprecated - use executeWeaponMove instead
    // Keeping for backward compatibility if needed
    return calculate_move_type_damage(enemy.equipped_weapon, move, enemy.wisdom_level, 1.0f);
}

Enemy enemies[4] = {
    {
        "Iron-Skinned Goblin",
        "A glint of wickedness flashes in its crooked grin",
        {6, 5, 8, 100, 100},
        {0}, // equipped_weapon - initialized later
        {{NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}},
        0 // wisdom level
    },
    {
        "Granite Naga",
        "The ground trembles as the Granite Naga uncoils from around a temple pillar",
        {10, 8, 4, 100, 100},
        {0}, // equipped_weapon - initialized later
        {{NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}},
        0 // wisdom level
    },
    {
        "Willow Wisp",
        "The air grows cold as a Neon Willow-Wisp circles you",
        {4, 3, 12, 100, 100},
        {0}, // equipped_weapon - initialized later
        {{NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}},
        0 // wisdom level
    },
    {
        "Storm-Winged Gryphon",
        "At the highest peak, the Storm-Winged Gryphon awaits",
        {12, 10, 6, 100, 100},
        {0}, // equipped_weapon - initialized later
        {{NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}},
        0 // wisdom level
    }
};

// Initialize enemy weapons
void initialize_enemy_weapons() {
    enemies[0].equipped_weapon = weapon_iron_fist();
    enemies[1].equipped_weapon = weapon_petrifying_slam();
    enemies[2].equipped_weapon = weapon_dazzling_thief();
    enemies[3].equipped_weapon = weapon_thunderous_cyclone();
}
