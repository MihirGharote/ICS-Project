#include "./renderWindows.h"
#include "../globals.h"
#include "./levelWindow.h"
#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

static void _bomb(char *error_msg);

const chtype A_HEADER = COLOR_PAIR(COLOR_CYAN) | A_BOLD;

void initncurses() {
    initscr();
    cbreak();
    curs_set(0);

    if (!has_colors()) {
        _bomb("Your terminal does not support colors\n");
    }

    if (start_color() != OK) {
        _bomb("Unable to start colors\n");
    }

    for (short i = 0; i <= 7; i++) {
        init_pair(i, i, COLOR_BLACK);
    }
}

void initWindows() {
    assert(mainwin == NULL);
    assert(levelwin == NULL);
    assert(choicewin == NULL);

    refresh();
    int right_w = 15;
    int bottom_h = 9;

    int main_h = LINES - bottom_h;
    int main_w = COLS - right_w;

    mainwin = newwin(main_h, main_w, 0, 0);
    levelwin = newwin(LINES, right_w, 0, main_w);
    choicewin = newwin(bottom_h, main_w, main_h, 0);

    box(mainwin, 0, 0);

    box(choicewin, 0, 0);
    keypad(choicewin, TRUE);

    refreshLevel();

    wrefresh(mainwin);
    wrefresh(levelwin);
    wrefresh(choicewin);
}

static void _bomb(char *error_msg) {
    exitncurses();
    fputs(error_msg, stderr);
    exit(1);
}

void exitncurses() {
    if (mainwin) {
        delwin(mainwin);
    }
    if (levelwin) {
        delwin(levelwin);
    }
    if (choicewin) {
        delwin(choicewin);
    }
    endwin();
}
