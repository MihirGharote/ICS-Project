#include <ncurses.h>

#ifndef DECISIONS_H
#define DECISIONS_H

typedef struct {
    int health_delta;   // Damage taken or healed
    int wisdom_delta;   // Wisdom gained
    int trigger_combat; // combat part
    int trigger_game;   // minigames part 
    char feedback[256];  
} Outcome;


int get_menu_choice(WINDOW *menu_win, char *options[], int count);


Outcome handle_encounter_1(int choice); // Naga 
Outcome handle_encounter_2(int choice); // Wisp 
Outcome handle_encounter_3(int choice); //  goblin
Outcome handle_encounter_4(int choice); // Final 

#endif