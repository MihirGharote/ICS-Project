#include "renderCombat.h"
#include "../combat/enemies.h"
#include "../globals.h"
#include <ncurses.h>

#define PADDING 5
#define INBETWEEN 10
#define LABELLENGTH 7 // The length of "HP" and "MANA"
#define VALUELENGTH 9 // The length of "  xxx/100"

static void renderBars(int enemyHP, int enemyMaxHP);

void renderCombat(Enemy *enemy) {
    werase(mainwin);
    box(mainwin, 0, 0);

    wattron(mainwin, A_HEADER);
    wattron(mainwin, COLOR_PAIR(COLOR_RED));
    mvwprintw(mainwin, 0, 2, " Combat ");
    wattroff(mainwin, COLOR_PAIR(COLOR_RED));
    wattroff(mainwin, A_HEADER);

    renderBars(enemy->stats.hp, enemy->stats.max_hp);
    wrefresh(mainwin);
    refresh();
}

static void renderBars(int enemyHP, int enemyMaxHP) {
    int hp = player.stats.hp;
    int maxhp = player.stats.max_hp;
    int barWidth = (getmaxx(mainwin) - 2 * PADDING - 2 * VALUELENGTH - INBETWEEN -
                   2 * LABELLENGTH - 2) / 2;
    
    // PLAYER
    mvwaddnstr(mainwin, 2, PADDING, "   HP ", LABELLENGTH);
    wattron(mainwin, COLOR_PAIR(COLOR_GREEN));
    if (((float)hp)/maxhp <= 0.5) {
        wattron(mainwin, COLOR_PAIR(COLOR_YELLOW));
    }
    if (((float)hp)/maxhp <= 0.2) {
        wattron(mainwin, COLOR_PAIR(COLOR_RED));
    }
    for (int i = 0; i < barWidth; i++) {
        if (i <= (barWidth*hp) / maxhp) {
            waddch(mainwin, ACS_BLOCK);
        } else {
            waddch(mainwin, ACS_CKBOARD);
        }
    }
    wattrset(mainwin, A_NORMAL);
    wprintw(mainwin, "  %-3d/%-3d", hp, maxhp);
    for (int i = 0; i < INBETWEEN; i++) {
        waddch(mainwin, ' ');
    }

    // ENEMY
    waddnstr(mainwin, "   HP ", LABELLENGTH);
    wattron(mainwin, COLOR_PAIR(COLOR_GREEN));
    if (((float)enemyHP)/enemyMaxHP <= 0.5) {
        wattron(mainwin, COLOR_PAIR(COLOR_YELLOW));
    }
    if (((float)enemyHP)/enemyMaxHP <= 0.2) {
        wattron(mainwin, COLOR_PAIR(COLOR_RED));
    }
    for (int i = 0; i < barWidth; i++) {
        if (i <= (barWidth*enemyHP) / enemyMaxHP) {
            waddch(mainwin, ACS_BLOCK);
        } else {
            waddch(mainwin, ACS_CKBOARD);
        }
    }
    wattrset(mainwin, A_NORMAL);
    wprintw(mainwin, "  %-3d/%-3d", enemyHP, enemyMaxHP);
}
