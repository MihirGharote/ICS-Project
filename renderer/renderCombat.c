#include "renderCombat.h"
#include "../globals.h"
#include <ncurses.h>

#define PADDING 5
#define INBETWEEN 10
#define LABELLENGTH 7 // The length of "HP" and "MANA"
#define VALUELENGTH 9 // The length of "  xxx/100"

void renderCombat() {
    werase(mainwin);
    box(mainwin, 0, 0);

    wattron(mainwin, A_HEADER);
    wattron(mainwin, COLOR_PAIR(COLOR_RED));
    mvwprintw(mainwin, 0, 2, " Combat ");
    wattroff(mainwin, COLOR_PAIR(COLOR_RED));
    wattroff(mainwin, A_HEADER);

    for (int i = 0; i <= 100; i++) {
        hp = i;
        renderBars(50, 50, 100, 100, 25, 25);
        wrefresh(mainwin);
        refresh();
        napms(10);
    }
    wrefresh(mainwin);
    refresh();
}

void renderBars(int mana, int maxMana, int enemyHP, int enemyMaxHP, int enemyMana, int enemyMaxMana) {
    int barWidth = (getmaxx(mainwin) - 2 * PADDING - 2 * VALUELENGTH - INBETWEEN -
                   2 * LABELLENGTH - 2) / 2;
    
    // PLAYER
    mvwaddnstr(mainwin, 2, PADDING, "   HP ", LABELLENGTH);
    for (int i = 0; i < barWidth; i++) {
        if ( i <= (barWidth*hp) / maxhp ) {
            waddch(mainwin, ACS_BLOCK);
        } else {
            waddch(mainwin, ACS_CKBOARD);
        }
    }
    wprintw(mainwin, "  %-3d/%-3d", hp, maxhp);
    for (int i = 0; i < INBETWEEN; i++) {
        waddch(mainwin, ' ');
    }

    // ENEMY
    waddnstr(mainwin, "   HP ", LABELLENGTH);
    for (int i = 0; i < barWidth; i++) {
        if (0) {
            waddch(mainwin, ACS_BLOCK);
        } else {
            waddch(mainwin, ACS_CKBOARD);
        }
    }
    wprintw(mainwin, "  %-3d/%-3d", enemyHP, enemyMaxHP);
}
