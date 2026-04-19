#include "./renderStory.h"
#include "../choice_handling/choice_system.h"
#include "../globals.h"
#include "../story2/printline.h"
#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#define INITIALX 3
#define DELAY 1

static void _render(char *s, int delay, int init_y);
static void _renderFile(char *file, int delay);
static void _renderEvent(char *event);
static void _renderTitle(char *title, int color);
static void delay_addstr(char *str, int delay);

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
    wrefresh(choicewin);
    refresh();
    switch (context) {
    case 0:
        _renderTitle("Introduction", COLOR_GREEN);
        napms(1000);
        _renderFile("./story2/firstline.txt", DELAY);
        break;
    case 1:
        _renderEvent("goblin");
        break;
    case 2:
        _renderEvent("granite_naga");
        break;
    case 3:
        _renderEvent("willow_wisp");
        break;
    case 4:
        _renderEvent("storm_winged_gryphon");
        break;
    case 6:
        _renderFile("story2/victory_end.txt", 10); // TODO: victory_end.txt
        break;
    case 7:
        _renderFile("story2/game_over.txt", 10); // TODO: game_over.txt
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

static void _renderTitle(char *title, int color) {
    wattron(mainwin, A_BOLD | COLOR_PAIR(color) | A_REVERSE);
    size_t n = strlen(title);
    wmove(mainwin, 1, (getmaxx(mainwin) - n)/2);
    for (int i = 0; i < n; i++) {
        waddch(mainwin, title[i]);
        napms(DELAY);
        wrefresh(mainwin);
        refresh();
    }
    napms(DELAY);
    wmove(mainwin, 1, (getmaxx(mainwin) - n)/2);
    wattroff(mainwin, A_REVERSE);
    for (int i = 0; i < n; i++) {
        waddch(mainwin, title[i]);
        napms(DELAY);
        wrefresh(mainwin);
        refresh();
    }
    wattroff(mainwin, A_BOLD | COLOR_PAIR(COLOR_RED) | A_REVERSE);
}

static void _renderEvent(char *event) {
    int x, y;
    char qualitiesFile[64], introFile[64];
    sprintf(introFile, "./story2/encounter_%s.txt", event);
    sprintf(qualitiesFile, "./story2/qualities_%s.txt", event);

    FILE *intro = fopen(introFile, "r");
    FILE *qualities = fopen(qualitiesFile, "r");

    char title[64];
    char encounterMsg[512];
    fscanf(intro, "%[^\n]\n%[^\n]", title, encounterMsg);

    char qualityDesc[512];
    char power1[64];
    char desc1[128];
    char power2[64];
    char desc2[128];
    char behavior[512];
    fscanf(qualities,
           "Qualities: %[^\n]\n"
           "Powers: [%[^]]] (%[^)]) and [%[^]]] (%[^)])\n"
           "%[^\n]",
           qualityDesc, power1, desc1, power2, desc2, behavior);

    fclose(intro);
    fclose(qualities);

    _renderTitle(title, COLOR_RED);
    napms(2*DELAY);
    _render(encounterMsg, DELAY, 3);
    wattron(mainwin, A_ITALIC);
    _render(qualityDesc, DELAY, 0);
    wattroff(mainwin, A_ITALIC);
    _render("", 0, 0);  // Blank line
    _render("Enemy Moves:\n", DELAY, 0);

    napms(500);
    delay_addstr("  - ", 0);
    wattron(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
    delay_addstr(power1, DELAY);
    wattroff(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
    delay_addstr(": ", 0);
    wattron(mainwin, COLOR_PAIR(COLOR_CYAN) | A_ITALIC);
    delay_addstr(desc1, DELAY);
    wattroff(mainwin, COLOR_PAIR(COLOR_CYAN) | A_ITALIC);
    _render("", 0, 0);
    
    wrefresh(mainwin);
    refresh();
    napms(500);
    
    delay_addstr("  - ", 0);
    wattron(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
    delay_addstr(power2, DELAY);
    wattroff(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
    delay_addstr(": ", 0);
    wattron(mainwin, COLOR_PAIR(COLOR_CYAN) | A_ITALIC);
    delay_addstr(desc2, DELAY);
    wattroff(mainwin, COLOR_PAIR(COLOR_CYAN) | A_ITALIC);
    _render("", 0, 0);
    
    wrefresh(mainwin);
    refresh();
    napms(500);

    _render(behavior, 2*DELAY, 0);
}

static void delay_addstr(char *str, int delay) {
    for (int i = 0; i < strlen(str); i++) {
        waddch(mainwin, str[i]);
        wrefresh(mainwin);
        refresh();
        napms(delay);
    }
}

static void _renderFile(char *file, int delay) {
    _render(read_file_to_string(file), delay, 3);
}

static void _render(char *s, int delay, int init_y) {
    int wcols;
    wcols = getmaxx(mainwin);
    int y, x;
    int width = wcols - 4;
    int filled = 0;

    if (init_y) {
        wmove(mainwin, init_y, INITIALX);
    } else {
        // Move to next line
        getyx(mainwin, y, x);
        wmove(mainwin, y + 1, INITIALX);
    }
    while (*s) {
        getyx(mainwin, y, x);
        char *sp = strchr(s, ' ');
        if (!sp)
            sp = s + strlen(s);
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