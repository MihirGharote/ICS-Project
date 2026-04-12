#include <stdio.h>
#include "printline.h"
#include "qualities.h"
int main() {
    printline("encounter_granite_naga.txt");
   const char *traits = get_traits("granite_naga");

if(traits != NULL)
{
    printw("%s", traits);
}
    return 0;
}