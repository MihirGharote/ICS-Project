#include "../globals.h"
#include "./items.h"
#include "./player.h"

void createPlayer() {
    player = (Player){
        "Hero",
        {5, 4, 6, 200, 200}, 
        get_evolved_weapon(0, 1), // wisdom_level=1 (intiially)
        { {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0}, {NO_STATUS, 0} },
        {item_antidote()}, // inventory
        1, 
        1 
    };
}