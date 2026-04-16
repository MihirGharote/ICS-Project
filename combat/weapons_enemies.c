/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./items.h"

// Enemy weapons - one per enemy, no transformations

// Goblin: Iron Fist - high physical defense, whacking damage
Weapon weapon_iron_fist(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Iron Fist", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "A metallic punch that doubles defense when used!", MAX_ITEM_DESC - 1);
    w.base_damage = 12;
    w.dmg_type = DMG_WHACKING | DMG_PUNCH;
    return w;
}

// Granite Naga: Petrifying Slam - combines petrifying gaze and earthquake slam
Weapon weapon_petrifying_slam(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Petrifying Slam", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "A stone-turning, ground-shaking strike that stuns and poisons!", MAX_ITEM_DESC - 1);
    w.base_damage = 18;
    w.dmg_type = DMG_WHACKING | DMG_POISON | DMG_SLASH;
    return w;
}

// Willow Wisp: Dazzling Thief - combines dazzling flash and will-o'-the-thief
Weapon weapon_dazzling_thief(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Dazzling Thief", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "A blinding, sneaky attack that disorients and drains!", MAX_ITEM_DESC - 1);
    w.base_damage = 10;
    w.dmg_type = DMG_LIGHTNING | DMG_STAB | DMG_THROW;
    return w;
}

// Storm-Winged Gryphon: Thunderous Cyclone - combines thunderous screech and cyclone shield
Weapon weapon_thunderous_cyclone(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Thunderous Cyclone", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "A deafening, swirling storm that shocks and reflects!", MAX_ITEM_DESC - 1);
    w.base_damage = 15;
    w.dmg_type = DMG_LIGHTNING | DMG_SLASH | DMG_SHOOT;
    return w;
}
*/