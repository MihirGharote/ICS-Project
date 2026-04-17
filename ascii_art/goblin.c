#include <stdio.h>

int main() {
    printf("\n========================================================================\n");
    printf("The Iron-Skinned Goblin sneers at you, blocking the exit.\n");
    printf("Its skin clangs like a bell when it moves.\n");
    printf("How will you proceed to earn your first Shard?\n");
    printf("========================================================================\n\n");
    
    printf("    .-\"-.\n");
    printf("   | o_o |\n");
    printf("  /[#####]\\\n");
    printf("  | [###] |\n");
    printf("   \\_/^\\_/\n\n");

    printf("================= IRON-SKINNED GOBLIN ==================================\n");
    printf(" Qualities: High physical defense, clumsy movement, obsessed with shiny objects.\n");
    printf(" Powers:    [Metallic Hardening] (doubles defense)\n");
    printf("            [Iron Fist] \n");
    printf("========================================================================\n\n");
    
    printf("What will you do?\n");
    printf("  [1] Combat: Sword Duel\n");
    printf("  [2] Minigame: Bribe with Jewels !!\n");
    printf("\nChoice: ");
    
    char choice;
    scanf(" %c", &choice);
    
    printf("\n");
    if (choice == '1') {
        printf(">> You draw your sword. The Goblin clangs its fists together!\n");
    } else if (choice == '2') {
        printf(">> You pull out a shiny ruby. The Goblin's eyes go wide...\n");
    } else {
        printf(">> You hesitate. The Goblin swings its Iron Fist!\n");
    }
    printf("\n");
    return 0;
}
