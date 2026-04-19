#include "./renderer/renderWindows.h"
#include "./renderer/renderStory.h"
#include "./renderer/renderCombat.h"
#include "./choice_handling/mainloop.h"
#include <ncurses.h>

int main() {
    initncurses();
    initWindows();
    renderStory(0);
    nextChoice();
    //renderStory(1);
    //nextChoice();
    start_mainloop();
    //renderCombat();
    nextChoice();
    exitncurses();
}