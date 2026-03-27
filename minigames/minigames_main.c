#include <stdio.h>

int main() {
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
