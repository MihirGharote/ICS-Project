#if defined(__has_include)
#  if __has_include(<ncurses.h>)
#    include <ncurses.h>
#  elif __has_include(<curses.h>)
#    include <curses.h>
#  else
#    include <stdio.h>
#    define printw printf
#    define refresh() ((void)0)
#  endif
#else
#  include <ncurses.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./items.h"

// what damage will be dome by each type
int dmg_base_values[] = {
    [0] = 5,   // PUNCH
    [1] = 15,  // SLASH
    [2] = 10,  // WHACKING
    [3] = 20,  // STAB
    [4] = 15,  // THROW
    [5] = 10,  // FRONTKICK
    [6] = 15,  // AXEKICK
    [7] = 15,  // SIDEKICK
    [8] = 25,  // FIRE
    [9] = 25,  // LIGHTNING
    [10] = 15, // SHOOT
    [11] = 5   // POISON 
};

// Calculation of the damage dealt by weapon

int calculate_weapon_damage(Weapon w, int wisdom_level, float strength_factor) {
    int total_from_types = 0;
    float wisdom_mult = 1.0f + (wisdom_level * 0.10f); 

    for (int i = 0; i < 12; i++) {
        if (w.dmg_type & (1 << i)) {
            total_from_types += dmg_base_values[i];
        }
    }
    float final_dmg = ((total_from_types + w.base_damage) * wisdom_mult * strength_factor);

    return (int)roundf(final_dmg);
}

int calculate_defense(Armor a, int wisdom_level) {
    float wisdom_def_bonus = 1.0f + (wisdom_level * 0.05f);
    float final_def = (a.defense_value * wisdom_def_bonus);
    return (int)roundf(final_def);
}

// Initial sets of the weapons
Weapon weapon_bare_hands(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Bare Hands", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "This is all I have....and it is ENOUGH!!", MAX_ITEM_DESC - 1);
    w.base_damage = 3;
    w.dmg_type = DMG_PUNCH | DMG_FRONTKICK;
    return w;
}

Weapon weapon_ancient_sword(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Ancient Sword", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "The sword of the DEAD!!", MAX_ITEM_DESC - 1);
    w.base_damage = 6;
    w.dmg_type = DMG_SLASH | DMG_STAB;
    return w;
}

Weapon weapon_mallet(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Wooden Mallet", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "I shall MEND my OWN way!!", MAX_ITEM_DESC - 1);
    w.base_damage = 8;
    w.dmg_type = DMG_WHACKING;
    return w;
}

Weapon weapon_gada(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Iron Gada",MAX_ITEM_NAME - 1);
    strncpy(w.desc, "The last thing you'll SEE!!", MAX_ITEM_DESC - 1);
    w.base_damage = 8;
    w.dmg_type = DMG_WHACKING;
    return w;
}

Weapon weapon_bow(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Short Bow", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "They whisper your name already!!", MAX_ITEM_DESC - 1);
    w.base_damage = 4;
    w.dmg_type = DMG_SHOOT;
    return w;
}

Weapon weapon_fiery_sword(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Fiery Sword", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "May thy knife CHIP and SHATTER!!", MAX_ITEM_DESC - 1);
    w.base_damage = 10;
    w.dmg_type = DMG_SLASH | DMG_FIRE; 
    return w;
}

Weapon weapon_shadow_dagger(void) {
    Weapon w; memset(&w, 0, sizeof(w));
    strncpy(w.name, "Dagger", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "By the time you notice...it's OVER!!",MAX_ITEM_DESC - 1);
    w.base_damage = 5;
    w.dmg_type = DMG_THROW | DMG_STAB;
    return w;
}
//Level 2+ LEGENDARY EVOLUTIONS 

Weapon weapon_gilgamesh_knuckles(void) {
    Weapon w = weapon_bare_hands();
    strncpy(w.name, "Knuckles of Gilgamesh", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "A king needs NO blade!!", MAX_ITEM_DESC - 1);
    w.base_damage = 12;
    w.dmg_type |= DMG_AXEKICK | DMG_SIDEKICK; 
    return w;
}

Weapon weapon_anduril(void) {
    Weapon w = weapon_ancient_sword();
    strncpy(w.name, "Andúril", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "The flame of the past shall NOT fade!!", MAX_ITEM_DESC - 1);
    w.base_damage = 15;
    return w;
}

Weapon weapon_mjolnir(void) {
    Weapon w = weapon_mallet();
    strncpy(w.name, "Mjolnir", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "Only the worthy REMAINS standing!!", MAX_ITEM_DESC - 1);
    w.base_damage = 20;
    w.dmg_type |= DMG_THROW | DMG_LIGHTNING;
    return w;
}

Weapon weapon_hanuman_gada(void) {
    Weapon w = weapon_gada();
    strncpy(w.name, "Hanuman's Gada", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "Let righteousness carry this BLOW!!", MAX_ITEM_DESC - 1);
    w.base_damage = 22;
    w.dmg_type |= DMG_SIDEKICK;
    return w;
}

Weapon weapon_gandiv(void) {
    Weapon w = weapon_bow();
    strncpy(w.name, "Gandiv", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "Where I aim, fate FOLLOWS!!", MAX_ITEM_DESC - 1);
    w.base_damage = 20;
    w.dmg_type |= DMG_LIGHTNING | DMG_FIRE;
    return w;
}

Weapon weapon_amaterasu_beast(void) {
    Weapon w = weapon_fiery_sword();
    strncpy(w.name, "Amaterasu's Beast", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "Dawn has chosen its END!!", MAX_ITEM_DESC - 1);
    w.base_damage = 15;
    w.dmg_type |= DMG_STAB | DMG_POISON;
    return w;
}

Weapon weapon_dagger_of_peleus(void) {
    Weapon w = weapon_shadow_dagger();
    strncpy(w.name, "Dagger of Peleus", MAX_ITEM_NAME - 1);
    strncpy(w.desc, "Glory is paid in BLOOD!!", MAX_ITEM_DESC - 1);
    w.base_damage = 15;
    w.dmg_type |= DMG_POISON | DMG_FIRE | DMG_LIGHTNING;
    return w;
}

// Evolution switches

Weapon get_evolved_weapon(int slot_id, int wisdom_level) {
    switch(slot_id) {
        case 0: return (wisdom_level >= 2) ? weapon_gilgamesh_knuckles() : weapon_bare_hands();
        case 1: return (wisdom_level >= 3) ? weapon_anduril() : weapon_ancient_sword();
        case 2: return (wisdom_level >= 5) ? weapon_mjolnir() : weapon_mallet();
        case 3: return (wisdom_level >= 6) ? weapon_hanuman_gada() : weapon_gada();
        case 4: return (wisdom_level >= 5) ? weapon_gandiv() : weapon_bow();
        case 5: return (wisdom_level >= 3) ? weapon_amaterasu_beast() : weapon_fiery_sword();
        default: return weapon_bare_hands();
    }
}

Armor get_evolved_shield(int wisdom_level) {
    if (wisdom_level >= 4) return armor_aegis();
    return armor_basic_shield();
}

// shield

Armor armor_basic_shield(void) {
    Armor a; memset(&a, 0, sizeof(a));
    strncpy(a.name, "Wooden Shield", MAX_ITEM_NAME - 1);
    strncpy(a.desc, "As long as this stands...so do I!!", MAX_ITEM_DESC - 1);
    a.defense_value = 10;
    return a;
}

Armor armor_aegis(void) {
    Armor a; memset(&a, 0, sizeof(a));
    strncpy(a.name, "Aegis", MAX_ITEM_NAME - 1);
    strncpy(a.desc, "Look upon me and FALTER!!", MAX_ITEM_DESC - 1);
    a.defense_value = 50;
    return a;
}

// --- ITEM WRAPPERS ---

Item item_from_weapon(Weapon w, int gold_value) {
    Item it; memset(&it, 0, sizeof(it));
    strncpy(it.name, w.name, MAX_ITEM_NAME - 1);
    strncpy(it.desc, w.desc, MAX_ITEM_DESC - 1);
    it.type = ITEM_WEAPON;
    it.value = gold_value;
    it.data.weapon = w;
    return it;
}

Item item_from_armor(Armor a, int gold_value) {
    Item it; memset(&it, 0, sizeof(it));
    strncpy(it.name, a.name, MAX_ITEM_NAME - 1);
    strncpy(it.desc, a.desc, MAX_ITEM_DESC - 1);
    it.type = ITEM_ARMOR;
    it.value = gold_value;
    it.data.armor = a;
    return it;
}

// --- CONSUMABLES ---

Item item_health_potion(int heal_amount) {
    Item it; memset(&it, 0, sizeof(it));
    snprintf(it.name, 47, "Health Potion (%d)", heal_amount);
    it.type = ITEM_CONSUMABLE;
    it.data.consumable.heal_hp = heal_amount;
    return it;
}

Item item_antidote(void) {
    Item it; memset(&it, 0, sizeof(it));
    strncpy(it.name, "Antidote", MAX_ITEM_NAME - 1);
    strncpy(it.desc, "A bitter brew that purges toxins.", MAX_ITEM_DESC - 1);
    it.type = ITEM_CONSUMABLE;
    it.data.consumable.cure_poison = 1; // Flag to be checked in use_item
    return it;
}

void cure_poison(StatusEffect active_effects[]) {
    int cured = 0;
    for (int i = 0; i < 4; i++) {
        if (active_effects[i].status & POISON) {
            active_effects[i].status = NO_STATUS;
            active_effects[i].severity = 0;
            cured = 1;
        }
    }
    if (cured) {
        printw("Antidote used! The poison is gone.\n");
        refresh();
    }
}

void use_item(Item *it, Stats *player_stats, StatusEffect player_afflictions[]) {
    if (it->type != ITEM_CONSUMABLE) return;

    if (it->data.consumable.heal_hp > 0) {
        player_stats->hp += it->data.consumable.heal_hp;
        if (player_stats->hp > player_stats->max_hp) 
            player_stats->hp = player_stats->max_hp;
    }
    if (it->data.consumable.cure_poison) {
        cure_poison(player_afflictions);
    }
}

