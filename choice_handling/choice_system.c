#include <ncurses.h>
#include "decision.h"
#include "../globals.h"

int get_menu_choice(WINDOW *menu_win, char *options[], int count) {
    int highlight = 0;
    int choice = -1;
    int key;

    flushinp();

    while(1) {
        werase(menu_win);
        box(menu_win, 0, 0);
        wattron(menu_win, A_HEADER);
        mvwprintw(menu_win, 0, 2, " Choices ");
        wattroff(menu_win, A_HEADER);

        for(int i = 0; i < count; i++) {
            if(i == highlight) {
                wattron(menu_win, COLOR_PAIR(COLOR_GREEN) | A_BOLD); 
                mvwprintw(menu_win, i + 2, 2, ">");
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 2, 4, "%s", options[i]);
                wattroff(menu_win, COLOR_PAIR(COLOR_GREEN) | A_BOLD | A_REVERSE); 
            } else {
                mvwprintw(menu_win, i + 2, 4, "%s", options[i]);
            }
        }

        wrefresh(menu_win);
        key = wgetch(menu_win);

        switch(key) {
            case KEY_UP:
                highlight = (highlight == 0) ? count - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == count - 1) ? 0 : highlight + 1;
                break;
            case 10: // ENTER Key part
                choice = highlight + 1;
                break;
        }
        if(choice != -1) break;
    }
    
   
    return choice;
}