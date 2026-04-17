#include <string.h>
#include "qualities.h"

const char *get_traits(const char *character_name)
{
    if(strcmp(character_name, "goblin") == 0)
    {
        return
        "Qualities: High physical defense, clumsy movement, obsessed with shiny objects.\n"
        "Powers: Metallic Hardening (doubles defense), Iron Fist.\n"
        "Encounter: The Iron-Skinned Goblin sneers at you, blocking the exit.\n"
        "Choice: [Combat: Sword Duel] or [Minigame: Bribe with Jewels]";
    }

    if(strcmp(character_name, "willow_wisp") == 0)
    {
        return
        "Qualities: Extremely fast, intangible (hard to hit), emits a calming aroma.\n"
        "Powers: [Dazzling Flash] (blinds the opponent) and [Will-o'-the-Thief] (steals points).\n"
        "Encounter: The air grows cold as a Neon Willow-Wisp circles you. It wants your memories.\n"
        "Choice: [Combat: Magic Blast] or [Minigame: Light-Speed Chase]";
    }

    if(strcmp(character_name, "granite_naga") == 0)
    {
        return
        "Qualities: Immense strength, slow-acting venom, patient hunter.\n"
        "Powers: [Petrifying Gaze] (turns limbs to stone) and [Earthquake Slam] (stuns the player).\n"
        "Encounter: The ground trembles as the Granite Naga uncoils from around a temple pillar.\n"
        "Choice: [Combat: Tactical Strike] or [Minigame: Ancient Rune Puzzle]";
    }

    if(strcmp(character_name, "gryphon") == 0)
    {
        return
        "Qualities: Prideful, master of the winds, lightning-fast reflexes.\n"
        "Powers: [Thunderous Screech] (lowers attack power) and [Cyclone Shield] (reflects projectiles).\n"
        "Encounter: At the highest peak, the Gryphon awaits. The sky turns black as it spreads its wings.\n"
        "Choice: [Combat: Aerial Battle] or [Minigame: Sky-Rider Balance]";
    }

    return NULL;
}

