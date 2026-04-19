#include "./renderWindows.h"
#include "../globals.h"
#include "../ascii_art/ascii.h"
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

    if (LINES < 25 || COLS < 80) {
        char error[64];
        sprintf(error, "Current Resolution: %dx%d | Required: 80x25 or larger.", COLS, LINES);
        _bomb(error);
    }

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

void logo() {
    int w, h;
    char **art = getAsciiArt("./ascii_art/logo.txt", &w, &h);
    for (int i = 0; i < h; i++) {
        if (i >= 18) {
            wattrset(stdscr, A_BOLD);
        }
        mvaddstr(i, 0, art[i]);
    }
    freeAsciiArt(art, w, h);

    wattrset(stdscr, A_BOLD | A_UNDERLINE | COLOR_PAIR(COLOR_RED));
    mvaddstr(getmaxy(stdscr) - 1, (w - 30)/2, "[ Press any key to continue ]");
    wattrset(stdscr, A_NORMAL);
    getch();
    erase();
    refresh();
    flash();
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
    exit(EXIT_FAILURE);
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
