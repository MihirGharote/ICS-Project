#include "./renderWindows.h"
#include <ncurses.h>

int renderer_main() {
    initncurses();
    initWindows();
    getch();
    return 0;
}
