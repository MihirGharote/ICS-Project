#include "./renderer/renderWindows.h"
#include "./renderer/renderStory.h"
#include "./renderer/renderCombat.h"
#include "./choice_handling/mainloop.h"
#include "combat/player.h"
#include <ncurses.h>

int main() {
    initncurses();
    logo();
    initWindows();
    createPlayer();
    renderStory(0);
    nextChoice();
    //renderStory(1);
    //nextChoice();
    start_mainloop();
    //renderCombat();
    nextChoice();
    exitncurses();
}