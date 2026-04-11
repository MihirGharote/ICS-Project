#include <stdio.h>
#include <string.h>
#include "decision.h"

// ENCOUNTER 1: NAGA
Outcome process_naga_choice(int choice) {
    Outcome out = {0, 0, 0, 0, ""}; // Initialize everything to zero/empty

    if (choice == 1) { // Option 1: Basic Shield (Defensive Event)
        out.health_delta = -10;
        out.wisdom_delta = 5;
        strcpy(out.feedback, "You blocked the strike, but the venom stung your arm!");
    } 
    else if (choice == 2) { // Option 2: Strike (Triggers Samarth's Combat)
        out.trigger_combat = 1; 
        strcpy(out.feedback, "You draw your blade! Prepare for combat!");
    } 
    else { // Option 3: Use Fiery Sword (Event)
        out.health_delta = -20;
        out.wisdom_delta = -5;
        strcpy(out.feedback, "The steam from the water scalds you! Bad move.");
    }
    return out;
}

// ENCOUNTER 2: WILL-O'-WISP
Outcome process_wisp_choice(int choice) {
    Outcome out = {0, 0, 0, 0, ""};

    if (choice == 1) { // Option 1: Bare Hands (Event Failure)
        out.health_delta = -40;
        out.wisdom_delta = 5;
        strcpy(out.feedback, "Your fists find only cold mist. The Wisps drain your soul!");
    } 
    else if (choice == 2) { // Option 2: Solve the Puzzle (Triggers Priyal's Minigame)
        out.trigger_game = 1;
        strcpy(out.feedback, "The spirits challenge your mind! Quick, solve it!");
    }
    else { // Option 3: Mjolnir (Instant Success)
        out.health_delta = 0;
        out.wisdom_delta = 30;
        strcpy(out.feedback, "Lightning erases the darkness! The spirits vanish.");
    }
    return out;
}