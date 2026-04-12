#include <stdio.h>
#include "printline.h"
#include "qualities.h"

int main() {
    printline("encounter_goblin.txt");
 const char *traits = get_traits("encounter_goblin");

if(traits != NULL)
{
    printw("%s", traits);
}
    return 0;
}