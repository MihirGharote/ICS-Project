#pragma once

#include <ncurses.h>
#include <stdio.h>

extern int level;
extern unsigned int wisdom;
extern unsigned int maxhp;
extern unsigned int hp;

extern WINDOW *mainwin;
extern WINDOW *choicewin;
extern WINDOW *levelwin;

extern const chtype A_HEADER;