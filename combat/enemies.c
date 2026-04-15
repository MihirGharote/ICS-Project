#include <stdio.h>
#include <stdlib.h>

#include "./enemies.h"

int getEnemyDamage(Enemy enemy, unsigned short move) {
    // This function is deprecated - use executeWeaponMove instead
    // Keeping for backward compatibility if needed
    return calculate_move_type_damage(enemy.equipped_weapon, move, enemy.wisdom_level, 1.0f);
}

Enemy enemies[1] = {
    {
        "Goblin",
        "A glint of wickedness flashes in its crooked grin",
        {6, 5, 8, 100, 100},
        {0}, // equipped_weapon - will be initialized with weapon_gada() at runtime or set here
        {{NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}},
        2 // wisdom level
    }
};
