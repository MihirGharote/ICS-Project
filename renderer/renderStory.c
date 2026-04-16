#include "./renderStory.h"
#include "../choice_handling/choice_system.h"
#include "../globals.h"
#include "../story2/printline.h"
#include <assert.h>
#include <string.h>
#include <ncurses.h>

#define INITIALX 2

static void _render(char *file, int delay);

void renderStory(int context) {
    werase(mainwin);
    box(mainwin, 0, 0);
    
    wattron(mainwin, A_HEADER);
    mvwprintw(mainwin, 0, 2, " Story ");
    wattroff(mainwin, A_HEADER);

    werase(choicewin);
    box(choicewin, 0, 0);
    wattron(choicewin, A_HEADER);
    mvwprintw(choicewin, 0, 2, " Choices ");
    wattroff(choicewin, A_HEADER);
    switch (context) {
    case 0:
        _render("./story2/firstline.txt", 25);
        break;
    case 1:
        _render("./choice_handling/naga_intro.txt", 25);
        break;
    default:
        break;
    }
    wrefresh(mainwin);
    refresh();
}

void nextChoice() {
    char *opt[1] = {"Next"};
    get_menu_choice(choicewin, opt, 1);
}

static void _render(char *file, int delay) {
    char *s = read_file_to_string(file);

    int wcols; wcols = getmaxx(mainwin);
    int y, x;
    int width = wcols - 4;
    int filled = 0;

    wmove(mainwin, 2, INITIALX);
    while (*s) {
        getyx(mainwin, y, x);
        char *sp = strchr(s, ' ');
        if (!sp) sp = s + strlen(s);
        if (sp - s != 0 && *s != '\n') {
            if (sp - s <= width - filled) {
                while (sp - s != 0 && *s != '\n') {
                    filled++;
                    waddch(mainwin, *s);
                    s++;
                    napms(delay);
                    wrefresh(mainwin);
                    refresh();
                }
            } else {
                filled = 0;
                wmove(mainwin, y + 1, INITIALX);
                while (sp - s != 0) {
                    filled++;
                    waddch(mainwin, *s);
                    s++;
                    napms(delay);
                    wrefresh(mainwin);
                    refresh();
                }
            }
            continue;
        } else {
            if (*s == '\n' || filled >= width) {
                filled = 0;
                wmove(mainwin, y + 1, INITIALX);
                s++;
            } else {
                filled++;
                waddch(mainwin, *s);
                napms(delay);
                wrefresh(mainwin);
                refresh();
                s++;
            }
        }
    }
}