#include "renderCombat.h"
#include "../combat/enemies.h"
#include "../globals.h"
#include "../ascii_art/ascii.h"
#include <ncurses.h>
#include <string.h>

#define PADDING 5
#define INBETWEEN 10
#define LABELLENGTH 7 // The length of "HP" and "MANA"
#define VALUELENGTH 9 // The length of "  xxx/100"

#define playerCentre(bw, x) (PADDING + LABELLENGTH + (bw - x) / 2)
#define enemyCentre(bw, x)                                                     \
    (PADDING + 2 * LABELLENGTH + bw + VALUELENGTH + INBETWEEN + (bw - x) / 2)

static int renderBars(int enemyHP, int enemyMaxHP);
static void renderName(int barWidth, char *enemyName);

void renderCombat(Enemy *enemy) {
    werase(mainwin);
    box(mainwin, 0, 0);

    wattron(mainwin, A_HEADER);
    wattron(mainwin, COLOR_PAIR(COLOR_RED));
    mvwprintw(mainwin, 0, 2, " Combat ");
    wattroff(mainwin, COLOR_PAIR(COLOR_RED));
    wattroff(mainwin, A_HEADER);

    int barWidth = renderBars(enemy->stats.hp, enemy->stats.max_hp);
    renderName(barWidth, enemy->name);
    
    int pArtHeight, pArtWidth, eArtHeight, eArtWidth;
    char **playerArt = getAsciiArt("./ascii_art/hero.txt", &pArtWidth, &pArtHeight);
    renderArt(playerCentre(barWidth, pArtWidth), 4, playerArt, pArtWidth, pArtHeight);
    freeAsciiArt(playerArt, pArtWidth, pArtHeight);

    if (!strcmp(enemy->name, enemies[0].name)) {
        char **enemyArt = getAsciiArt("./ascii_art/goblin.txt", &eArtWidth, &eArtHeight);
        renderArt(enemyCentre(barWidth, eArtWidth), 4, enemyArt, eArtWidth, eArtHeight);
        freeAsciiArt(enemyArt, eArtWidth, eArtHeight);
    } else if (!strcmp(enemy->name, enemies[1].name)) {
        char **enemyArt = getAsciiArt("./ascii_art/granite_naga.txt", &eArtWidth, &eArtHeight);
        renderArt(enemyCentre(barWidth, eArtWidth), 4, enemyArt, eArtWidth, eArtHeight);
        freeAsciiArt(enemyArt, eArtWidth, eArtHeight);
    } else if (!strcmp(enemy->name, enemies[2].name)) {
        char **enemyArt = getAsciiArt("./ascii_art/willow_wisp.txt", &eArtWidth, &eArtHeight);
        renderArt(enemyCentre(barWidth, eArtWidth), 4, enemyArt, eArtWidth, eArtHeight);
        freeAsciiArt(enemyArt, eArtWidth, eArtHeight);
    } else if (!strcmp(enemy->name, enemies[3].name)) {
        char **enemyArt = getAsciiArt("./ascii_art/storm_winged_gryphon.txt", &eArtWidth, &eArtHeight);
        renderArt(enemyCentre(barWidth, eArtWidth), 4, enemyArt, eArtWidth, eArtHeight);
        freeAsciiArt(enemyArt, eArtWidth, eArtHeight);
    }

    wrefresh(mainwin);
    refresh();
}

static int renderBars(int enemyHP, int enemyMaxHP) {
    int hp = player.stats.hp;
    int maxhp = player.stats.max_hp;
    int barWidth = (getmaxx(mainwin) - 2 * PADDING - 2 * VALUELENGTH -
                    INBETWEEN - 2 * LABELLENGTH - 2) /
                   2;

    // PLAYER
    mvwaddnstr(mainwin, 2, PADDING, "   HP ", LABELLENGTH);
    wattron(mainwin, COLOR_PAIR(COLOR_GREEN));
    if (((float)hp) / maxhp <= 0.5) {
        wattron(mainwin, COLOR_PAIR(COLOR_YELLOW));
    }
    if (((float)hp) / maxhp <= 0.2) {
        wattron(mainwin, COLOR_PAIR(COLOR_RED));
    }
    for (int i = 0; i < barWidth; i++) {
        if (i <= (barWidth * hp) / maxhp) {
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
    if (((float)enemyHP) / enemyMaxHP <= 0.5) {
        wattron(mainwin, COLOR_PAIR(COLOR_YELLOW));
    }
    if (((float)enemyHP) / enemyMaxHP <= 0.2) {
        wattron(mainwin, COLOR_PAIR(COLOR_RED));
    }
    for (int i = 0; i < barWidth; i++) {
        if (i <= (barWidth * enemyHP) / enemyMaxHP) {
            waddch(mainwin, ACS_BLOCK);
        } else {
            waddch(mainwin, ACS_CKBOARD);
        }
    }
    wattrset(mainwin, A_NORMAL);
    wprintw(mainwin, "  %-3d/%-3d", enemyHP, enemyMaxHP);
    return barWidth;
}

static void renderName(int barWidth, char *enemyName) {
    size_t len1 = strlen(player.name);
    size_t len2 = strlen(enemyName);
    wattrset(mainwin, COLOR_PAIR(COLOR_GREEN) | A_BOLD);
    mvwaddnstr(mainwin, 3, playerCentre(barWidth, len1), player.name, len1);
    wattrset(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
    mvwaddnstr(mainwin, 3, enemyCentre(barWidth, len2), enemyName, len2);
    wattroff(mainwin, COLOR_PAIR(COLOR_RED) | A_BOLD);
}

void renderArt(int init_x, int init_y, char **art, int width,
                            int height) {
    for (int i = 0; i < height; i++) {
        mvwaddnstr(mainwin, init_y + i, init_x, art[i], width); 
    }
    wrefresh(mainwin);
    refresh();
}