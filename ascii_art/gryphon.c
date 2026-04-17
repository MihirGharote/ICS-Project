#include <stdio.h>

int main() {
    printf("\n========================================================================\n");
    printf("At the highest peak, the Storm-Winged Gryphon awaits.\n");
    printf("The sky turns black as it spreads its wings.\n");
    printf("This is the final guardian of your lost memory.\n");
    printf("========================================================================\n\n");
    
    printf("             ___\n");
    printf("            (o_o)\n");
    printf("           (  V  )\n");
    printf("   /------. \\   / .------\\\n");
    printf("  / |      \\ \\ / /      | \\\n");
    printf(" /  |       \\ | /       |  \\\n");
    printf(" `--|        \\|/        |--`\n");
    printf("    `---______|______---`\n");
    printf("             /|\\\n");
    printf("            / | \\\n");
    printf("           /  |  \\\n");
    printf("          /__/ \\__\\\n\n");

    printf("================= THE STORM-WINGED GRYPHON =============================\n");
    printf(" Qualities: Prideful, master of the winds, lightning-fast reflexes.\n");
    printf(" Powers:    [Thunderous Screech] (lowers attack power)\n");
    printf("            [Cyclone Shield]     (reflects projectiles)\n");
    printf("========================================================================\n\n");
    
    printf("What will you do?\n");
    printf("  [1] Combat: Aerial Battle\n");
    printf("  [2] Minigame: Sky-Rider Balance\n");
    printf("\nChoice: ");
    
    char choice;
    scanf(" %c", &choice);
    
    printf("\n");
    if (choice == '1') {
        printf(">> You draw your sword and leap into the turbulent sky!\n");
    } else if (choice == '2') {
        printf(">> You jump onto the Gryphon's back, trying to maintain balance!\n");
    } else {
        printf(">> You hesitate... The Gryphon unleashes a Thunderous Screech!\n");
    }
    printf("\n");
    return 0;
}
