#include <stdio.h>

int main() {
    printf("\n========================================================================\n");
    printf("The ground trembles as the Granite Naga uncoils from around a temple pillar.\n");
    printf("It speaks in a voice like grinding stones:\n");
    printf("'Only the worthy may pass the threshold of the mountain.'\n");
    printf("========================================================================\n\n");
    
    printf("    _ 0_0\n");
    printf("   /_|---'\n");
    printf("   [__]\n");
    printf("  /_/\n");
    printf("  [__]\n");
    printf("  \\__\\\n");
    printf("   [__]\n\n");

    printf("================= GRANITE NAGA =========================================\n");
    printf(" Qualities: Immense strength, slow-acting venom, patient hunter.\n");
    printf(" Powers:    [Petrifying Gaze] (turns limbs to stone)\n");
    printf("            [Earthquake Slam] (stuns the player)\n");
    printf("========================================================================\n\n");
    
    printf("What will you do?\n");
    printf("  [1] Combat: Tactical Strike\n");
    printf("  [2] Minigame: Ancient Rune Puzzle\n");
    printf("\nChoice: ");
    
    char choice;
    scanf(" %c", &choice);
    
    printf("\n");
    if (choice == '1') {
        printf(">> You target the weaknesses between its stone segments!\n");
    } else if (choice == '2') {
        printf(">> You focus on the glowing runes surrounding the temple pillar...\n");
    } else {
        printf(">> You turn to uncoil, but its Petrifying Gaze locks you in place!\n");
    }
    printf("\n");
    return 0;
}
