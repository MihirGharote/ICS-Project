
#include<stdio.h>
#include<string.h>
#include "decision.h"

// ENCOUNTER 1: Naga
Outcome handle_encounter_1(int choice) {
    Outcome out = {0, 0, 0, 0, ""};
    if (choice == 1) { // Block
        out.health_delta = -5;
        out.wisdom_delta = 5;
    } else if (choice == 2) { // Attack
        out.trigger_combat = 1; 
    }
    return out;
}

// ENCOUNTER 2: Wisp
Outcome handle_encounter_2(int choice) {
    Outcome out = {0, 0, 0, 0, ""};
    if (choice == 1) { // Ignore
        out.wisdom_delta = 10;
    } else if (choice == 2) { // Interact
        out.trigger_game = 1; 
    }
    return out;
}

// ENCOUNTER 3: Goblin
//ENCOUNTER 4: Final Boss