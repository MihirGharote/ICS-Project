#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "decision.h"

int get_menu_choice(WINDOW *menu_win, char *options[], int count) {
    int highlight = 0;
    int choice = -1;
    int key;

   //sub window creation and its dimensions
   // WINDOW *menu_win = newwin(10, COLS - 4, LINES - 11, 2);
    keypad(menu_win, TRUE); // Enable Arrow Keys

    while(1) {
        werase(menu_win);
        box(menu_win, 0, 0);
        mvwprintw(menu_win, 0, 2, " CHOICES ");

        for(int i = 0; i < count; i++) {
            if(i == highlight) {
                wattron(menu_win, A_REVERSE); 
                //highlighing part
                mvwprintw(menu_win, i + 2, 2, "> %s", options[i]);
                wattroff(menu_win, A_REVERSE);
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
            case 'q':
            case 'Q':
                endwin();
                exit(0);
        }
        if(choice != -1) break;
    }
    
   
    return choice;
}