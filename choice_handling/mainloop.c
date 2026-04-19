#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "../combat/items.h"
#include "../combat/player.h"
#include "../combat/combat.h"
#include "../globals.h"      
#include "../renderer/renderStory.h"
#include "../renderer/levelWindow.h"
#include "../minigames/minigames.h"
#include "./choice_system.h"
#include "./mainloop.h"

//Logic for a single encounter
 
static void execute_level() {
    Enemy villain;
    char result[64] = "TODO: Result";
    char *menu_opts[3] = {"", "", ""};
    Weapon w1, w2;

    // 1. DATA INITIALIZATION PER LEVEL
    switch(level) {
        case 1: // GOBLIN
            villain = enemies[0];
            villain.equipped_weapon = weapon_iron_fist();
            //strcpy(result, "story2/goblin_result.txt");
            w1 = weapon_bare_hands();
            w2 = weapon_ancient_sword();
            menu_opts[0] = "Attack: Bare Hands";
            menu_opts[1] = "Attack: Ancient Sword";
            menu_opts[2] = "Strategy: Tower of Hanoi";
            break;

        case 2: // NAGA
            villain = enemies[1];
            villain.equipped_weapon = weapon_petrifying_slam();
            //strcpy(result, "story2/naga_result.txt");
            w1 = weapon_mallet();
            w2 = weapon_fiery_sword();
            menu_opts[0] = "Attack: Wooden Mallet";
            menu_opts[1] = "Attack: Fiery Sword";
            menu_opts[2] = "Strategy: Reaction Test";
            break;

        case 3: // WISP
            villain = enemies[2];
            villain.equipped_weapon = weapon_dazzling_thief();
            //strcpy(result, "story2/wisp_result.txt");
            w1 = weapon_shadow_dagger();
            w2 = weapon_bow();
            menu_opts[0] = "Attack: Shadow Dagger";
            menu_opts[1] = "Attack: Short Bow";
            menu_opts[2] = "Strategy: Speed Arithmetic";
            break;

        case 4: // GRYPHON
            villain = enemies[3];
            villain.equipped_weapon = weapon_thunderous_cyclone();
            //strcpy(result, "story2/gryphon_result.txt");
            w1 = player.equipped_weapon; // Best current weapon
            w2 = weapon_anduril();    // Legendary find
            menu_opts[0] = "Attack: Current Weapon";
            menu_opts[1] = "Attack: Hero's Anduril";
            menu_opts[2] = "Strategy: Final Puzzle";
            break;
    }

    // 2. DISPLAY STORY & GET CHOICE
    renderStory(level);
    int choice = get_menu_choice(choicewin, menu_opts, 3);

    // 3. EXECUTE CHOICE
    if (choice == 1) {
        player.equipped_weapon = w1;
        startCombat(&villain);
    } 
    else if (choice == 2) {
        player.equipped_weapon = w2;
        startCombat(&villain);
    } 
    else if (choice == 3) {
        int success = 0;
        if (level == 1 || level == 4) success = play_hanoi();
        else if (level == 2) success = play_reaction();
        else success = play_arithmetic();

        if (success) {
            player.wisdom_level += 2; // Wisdom bonus for solving minigame
            //display_story_part(result);
        } else {
            // Failure leads to immediate combat with basic weapon
            startCombat(&villain);
        }
    }
    
    // 4. POST-ENCOUNTER UPDATES
    // Check if wisdom increased enough to evolve weapon
    player.equipped_weapon = get_evolved_weapon(level, player.wisdom_level);
}


 //The Game Flow (Sequential Encounters)

void start_mainloop() {    
    // Encounter sequence 1 -> 4
    for (int i = 1; i <= 4; i++) {
        level = i;
        refreshLevel(); // Updates the UI window on the right
        if (player.stats.hp <= 0) break; // Game Over check
        execute_level();
    }

    if (player.stats.hp > 0) {
        renderStory(6);
    } else {
        renderStory(7);
    }
}