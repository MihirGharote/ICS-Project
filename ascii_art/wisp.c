#include <stdio.h>

int main() {
    printf("\n========================================================================\n");
    printf("The air grows cold as a Neon Willow-Wisp circles you.\n");
    printf("It doesn't want your blood—it wants your memories.\n");
    printf("It dances just out of reach.\n");
    printf("========================================================================\n\n");
    
    printf("         *  .  *\n");
    printf("      *  \\\\ | // *\n");
    printf("    .   - -(O)- -   .\n");
    printf("      *  // | \\\\ *\n");
    printf("         *  .  *\n\n");

    printf("================= NEON WILLOW-WISP =====================================\n");
    printf(" Qualities: Extremely fast, intangible (hard to hit), emits a calming aroma.\n");
    printf(" Powers:    [Dazzling Flash] (blinds the opponent)\n");
    printf("            [Will-o'-the-Thief] (steals points)\n");
    printf("========================================================================\n\n");
    
    printf("What will you do?\n");
    printf("  [1] Combat: Magic Blast\n");
    printf("  [2] Minigame: Light-Speed Chase\n");
    printf("\nChoice: ");
    
    char choice;
    scanf(" %c", &choice);
    
    printf("\n");
    if (choice == '1') {
        printf(">> You unleash a Magic Blast, trying to disrupt its ethereal form!\n");
    } else if (choice == '2') {
        printf(">> You dart forward, trying to catch it in a Light-Speed Chase!\n");
    } else {
        printf(">> You are mesmerized by the aroma. It casts Will-o'-the-Thief!\n");
    }
    printf("\n");
    return 0;
}
