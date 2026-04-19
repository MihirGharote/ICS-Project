#include "./combat/player.h"
#include <ncurses.h>
#include <stdio.h>

int level = 1;
const int maxlevels = 4;

Player player;

WINDOW *mainwin = NULL;
WINDOW *choicewin = NULL;
WINDOW *levelwin = NULL;
