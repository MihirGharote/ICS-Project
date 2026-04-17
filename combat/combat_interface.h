#pragma once

#include "./player.h"
#include "./enemies.h"
#include "./items.h"
#include "./combat.h"

// Get current equipped weapon for player
Weapon* get_player_current_weapon(Player *player);

// Get name of a damage type (move type)
const char* get_move_type_name(int move_type_index);

// Get base damage value for a move type
int get_move_type_base_damage(int move_type_index);

// Get available move types for player's equipped weapon
// Returns array of move type indices and count
int get_player_available_moves(Player *player, int* out_move_indices, int max_count);

// Get all move type names for display
// Returns array of strings for all 12 move types
const char** get_all_move_type_names(void);

// Execute player's chosen move
// Returns message string
char* execute_player_choice_move(Player *player, Enemy *enemy, int move_type_index);

// Get enemy's random move for their turn
int get_enemy_random_move(Enemy *enemy);

// Execute enemy's move
// Returns message string
char* execute_enemy_choice_move(Enemy *enemy, Player *player, int move_type_index);
