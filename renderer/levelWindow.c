#include "../globals.h"
#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

void refreshLevel() {
    assert(levelwin);

    box(levelwin, 0, 0);
    wattron(levelwin, A_HEADER);
    mvwprintw(levelwin, 0, 2, " Levels ");
    wattroff(levelwin, A_HEADER);

    for (int i = 1; i <= maxlevels; i++) {
        if (i <= level) {
            wattrset(levelwin, COLOR_PAIR(COLOR_GREEN));
        }
        if (i == level) {
            wattron(levelwin, A_REVERSE | A_BOLD | A_UNDERLINE);
        }
        mvwprintw(levelwin, i+2, 2, "Level %2d", i);
        wattrset(levelwin, A_NORMAL);
    }

    wrefresh(levelwin);
    refresh();
}