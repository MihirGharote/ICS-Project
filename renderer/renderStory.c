#include "./renderStory.h"
#include "../choice_handling/choice_system.h"
#include "../globals.h"
#include "../story2/printline.h"
#include <assert.h>
#include <ctype.h>
#include <ncurses.h>

static void _render(char *file);

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
        _render("./story2/firstline.txt");
        break;
    case 1:
        _render("./choice_handling/naga_intro.txt");
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

static void _render(char *file) {
    const char *s = read_file_to_string(file);
    int wcols;
    int y, x;
    wcols = getmaxx(mainwin);
    wmove(mainwin, 1, 2);
    while (*s) {
        getyx(mainwin, y, x);
        int space = wcols - x - 7;
        if (space <= 0) {
            if (y + 1 >= getmaxy(mainwin))
                return;
            wmove(mainwin, y + 1, 2);
            continue;
        }
        if (*s == '\n') {
            wmove(mainwin, y + 1, 2);
            s++;
            continue;
        }

        int avail = 0;
        while (s[avail] && s[avail] != '\n' &&
               !iscntrl((unsigned char)s[avail]) && avail < space)
            avail++;
        if (s[avail] == '\0' || s[avail] == '\n') {
            waddnstr(mainwin, s, avail);
            wrefresh(mainwin);
            refresh();
            napms(1000);
            s += avail;
            continue;
        }

        int br = avail;
        while (br > 0 && !isspace((unsigned char)s[br]))
            br--;
        if (br == 0)
            br = avail;
        waddnstr(mainwin, s, br);
        s += br;
        while (*s && isspace((unsigned char)*s) && *s != ' ')
            s++;
    }
}