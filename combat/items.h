#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>

#define MAX_ITEM_NAME    48
#define MAX_ITEM_DESC    128

// Items
typedef enum {
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_CONSUMABLE,
    ITEM_KEY,
    ITEM_MISC,
} ItemType;

// Damage types
typedef enum {
    DMG_NONE       = 0,
    DMG_PUNCH      = (1 << 0),
    DMG_SLASH      = (1 << 1),
    DMG_WHACKING   = (1 << 2),
    DMG_STAB       = (1 << 3),
    DMG_THROW      = (1 << 4),
    DMG_FRONTKICK  = (1 << 5),
    DMG_AXEKICK    = (1 << 6),
    DMG_SIDEKICK   = (1 << 7),
    DMG_FIRE       = (1 << 8),
    DMG_LIGHTNING  = (1 << 9),
    DMG_SHOOT      = (1 << 10),
    DMG_POISON     = (1 << 11)
} DamageType;

// Weapons
typedef struct {
    char          name[MAX_ITEM_NAME];
    char          desc[MAX_ITEM_DESC];
    int           base_damage;
    DamageType    dmg_type;
} Weapon;

// Armor
typedef struct {
    char  name[MAX_ITEM_NAME];
    char  desc[MAX_ITEM_DESC];
    int   defense_value; 
    int   magic_resist;
    int   dodge_bonus;
} Armor;

// Consumable's effect
typedef struct {
    int heal_hp;
    int heal_mana;
    int cure_poison;
    int temp_attack_boost;
    int temp_boost_duration;
} ConsumableEffect;

// Items
typedef struct {
    char name[MAX_ITEM_NAME];
    char desc[MAX_ITEM_DESC];
    ItemType type;
    int value;
    union {
        Weapon           weapon;
        Armor            armor;
        ConsumableEffect consumable;
    } data;
} Item;

// Global Data Access
extern int dmg_base_values[];

// Logic funcns for combat and defence
int calculate_weapon_damage(Weapon w, int wisdom_level, float strength_factor);
int calculate_defense(Armor a, int wisdom_level);

// Evokution of the weapons based on wisdom level
Weapon get_evolved_weapon(int slot_id, int wisdom_level);
Armor get_evolved_shield(int wisdom_level);

// Bottom tier Weapons
Weapon weapon_bare_hands(void);
Weapon weapon_ancient_sword(void);
Weapon weapon_mallet(void);
Weapon weapon_gada(void);
Weapon weapon_bow(void);
Weapon weapon_fiery_sword(void);
Weapon weapon_shadow_dagger(void);

// Evoloved versions of the weapons
Weapon weapon_gilgamesh_knuckles(void);  // bare hands
Weapon weapon_anduril(void);  // ancient sword
Weapon weapon_mjolnir(void);  // mallet
Weapon weapon_hanuman_gada(void);  // gada
Weapon weapon_gandiv(void);  // bow
Weapon weapon_amaterasu_beast(void);  //fiery sword

// Shield
Armor armor_basic_shield(void);
Armor armor_aegis(void); // upgraded shield

// Item values and specification
Item item_from_weapon(Weapon w, int gold_value);
Item item_from_armor(Armor a, int gold_value);
Item item_health_potion(int heal_amount);
Item item_antidote(void);

#endif