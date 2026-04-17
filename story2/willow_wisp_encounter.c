#include <stdio.h>
#include "printline.h"
#include "qualities.h"
int main() {
    printline("encounter_willow_wisp.txt");
   const char *traits = get_traits("willow_wisp");

if(traits != NULL)
{
    printw("%s", traits);
}
    return 0;
}