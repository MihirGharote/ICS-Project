#include "minigames.h"
#include <stdio.h>

int play_arithmetic() {
    return 1;
}

int play_reaction() {
    return 1;
}

int play_hanoi() {
    return 1;
    printf("Minigames!\n");
    const char *art[] = {
        "                   A                   B                   C                   ",
        "                   |                   |                   |                   ",
        "                  ===                  |                   |                   ",
        "                 =====                 |                   |                   ",
        "                =======                |                   |                   ",
        "               =========               |                   |                   ",
        "              ===========              |                   |                   ",
        "===============================================================================",
        NULL
    };

    for (int i = 0; art[i] != NULL; ++i)
        puts(art[i]);

    return 0;
}
