#pragma once

#include <ncurses.h>
#include "decision.h"

int get_menu_choice(WINDOW *menu_win, char *options[], int count);