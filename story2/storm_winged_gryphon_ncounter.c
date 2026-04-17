#include <stdio.h>
#include "printline.h"
#include "qualities.h"
int main() {
    printline("encounter_storm_winged_gryphon.txt");
     const char *traits = get_traits("storm_winged_gryphon");

if(traits != NULL)
{
    printw("%s", traits);
}
    return 0;
}