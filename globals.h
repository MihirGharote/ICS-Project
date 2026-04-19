#pragma once

#include <ncurses.h>
#include <stdio.h>
#include "./combat/player.h"

extern int level;
extern const int maxlevels;
extern unsigned int wisdom;
extern unsigned int maxhp;
extern unsigned int hp;

extern Player player;

extern WINDOW *mainwin;
extern WINDOW *choicewin;
extern WINDOW *levelwin;

extern const chtype A_HEADER;