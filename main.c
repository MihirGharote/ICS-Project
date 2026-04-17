#include "./renderer/renderWindows.h"
#include "./renderer/renderStory.h"
#include <ncurses.h>

int main() {
    initncurses();
    initWindows();
    renderStory(0);
    nextChoice();
    renderStory(1);
    nextChoice();
    exitncurses();
}