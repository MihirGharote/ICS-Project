#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "./items.h"
#include "./player.h"
#include "./globals.h"      
#include "./renderStory.h"  

// External Minigame Prototypes
extern int play_hanoi();         
extern int play_reaction();   
extern int play_arithmetic();    

// External Combat & UI Prototypes
extern void startCombat(Player *p, Enemy *e);
extern void refreshLevel(); // Teammate's function to update Stats Window
extern int get_menu_choice(WINDOW *menu_win, char *options[], int count);


  //Loads and displays text files into the main story window
 
void display_story_part(const char *filename) {
    wclear(mainwin);
    box(mainwin, 0, 0);
    // Call teammate's file renderer or use a simple internal loop
    render_file_to_window(mainwin, filename); 
    wrefresh(mainwin);
}

  //Logic for a single encounter
 
void execute_level(Player *hero, int level_num) {
    Enemy villain;
    char intro[64], qualities[64], result[64];
    char *menu_opts[3];
    Weapon w1, w2;

    // 1. DATA INITIALIZATION PER LEVEL
    switch(level_num) {
        case 1: // GOBLIN
            villain = enemies[0];
            villain.equipped_weapon = weapon_iron_fist();
            strcpy(intro, "story2/encounter_goblin.txt");
            strcpy(qualities, "story2/qualities_goblin.txt");
            strcpy(result, "story2/goblin_result.txt");
            w1 = weapon_bare_hands();
            w2 = weapon_ancient_sword();
            menu_opts[0] = "Attack: Bare Hands";
            menu_opts[1] = "Attack: Ancient Sword";
            menu_opts[2] = "Strategy: Tower of Hanoi";
            break;

        case 2: // NAGA
            villain = enemies[1];
            villain.equipped_weapon = weapon_petrifying_slam();
            strcpy(intro, "story2/encounter_granite_naga.txt");
            strcpy(qualities, "story2/qualities_granite_naga.txt");
            strcpy(result, "story2/naga_result.txt");
            w1 = weapon_mallet();
            w2 = weapon_fiery_sword();
            menu_opts[0] = "Attack: Wooden Mallet";
            menu_opts[1] = "Attack: Fiery Sword";
            menu_opts[2] = "Strategy: Reaction Test";
            break;

        case 3: // WISP
            villain = enemies[2];
            villain.equipped_weapon = weapon_dazzling_thief();
            strcpy(intro, "story2/encounter_willow_wisp.txt");
            strcpy(qualities, "story2/qualities_willow_wisp.txt");
            strcpy(result, "story2/wisp_result.txt");
            w1 = weapon_shadow_dagger();
            w2 = weapon_bow();
            menu_opts[0] = "Attack: Shadow Dagger";
            menu_opts[1] = "Attack: Short Bow";
            menu_opts[2] = "Strategy: Speed Arithmetic";
            break;

        case 4: // GRYPHON
            villain = enemies[3];
            villain.equipped_weapon = weapon_thunderous_cyclone();
            strcpy(intro, "story2/encounter_storm_winged_gryphon.txt");
            strcpy(qualities, "story2/qualities_storm_winged_gryphon.txt");
            strcpy(result, "story2/gryphon_result.txt");
            w1 = hero->equipped_weapon; // Best current weapon
            w2 = weapon_anduril();    // Legendary find
            menu_opts[0] = "Attack: Current Weapon";
            menu_opts[1] = "Attack: Hero's Anduril";
            menu_opts[2] = "Strategy: Final Puzzle";
            break;
    }

    // 2. DISPLAY STORY & GET CHOICE
    display_story_part(intro);
    display_story_part(qualities);
    
    int choice = get_menu_choice(choicewin, menu_opts, 3);

    // 3. EXECUTE CHOICE
    if (choice == 1) {
        hero->equipped_weapon = w1;
        startCombat(hero, &villain);
    } 
    else if (choice == 2) {
        hero->equipped_weapon = w2;
        startCombat(hero, &villain);
    } 
    else if (choice == 3) {
        int success = 0;
        if (level_num == 1 || level_num == 4) success = play_hanoi();
        else if (level_num == 2) success = play_reaction();
        else success = play_arithmetic();

        if (success) {
            hero->wisdom_level += 2; // Wisdom bonus for solving minigame
            display_story_part(result);
        } else {
            // Failure leads to immediate combat with basic weapon
            startCombat(hero, &villain);
        }
    }

    // 4. POST-ENCOUNTER UPDATES
    // Check if wisdom increased enough to evolve weapon
    hero->equipped_weapon = get_evolved_weapon(level_num, hero->wisdom_level);
    refreshLevel(); // Updates the UI window on the right
}


 //The Game Flow (Sequential Encounters)

void start_game_flow() {
    // Initial setup
    Player hero = createPlayer(0); // Start with Bare Hands (slot 0)
    
    // Encounter sequence 1 -> 4
    for (int i = 1; i <= 4; i++) {
        if (hero.stats.hp <= 0) break; // Game Over check
        execute_level(&hero, i);
    }

    if (hero.stats.hp > 0) {
        display_story_part("story2/victory_end.txt");
    } else {
        display_story_part("story2/game_over.txt");
    }
}