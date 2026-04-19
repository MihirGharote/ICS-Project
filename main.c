#include "./renderer/renderWindows.h"
#include "./renderer/renderStory.h"
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
    start_mainloop();
    exitncurses();
}