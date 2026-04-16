#include <ncurses.h>
#include <stdio.h>

int level = 1;
unsigned int wisdom = 0;
unsigned int maxhp = 100;
unsigned int hp = 100;

WINDOW *mainwin = NULL;
WINDOW *choicewin = NULL;
WINDOW *levelwin = NULL;
