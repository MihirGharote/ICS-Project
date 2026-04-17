#include <stdio.h>

void draw_gryphon(const char* prefix) {
    printf("%s GRYPHON\n\n", prefix);
    printf("      /v\\\n");
    printf("   |\\\\0_0//|\n");
    printf("    \\\\_^_//\n");
    printf("     / | \\\n");
    printf("    /_ | _\\\n");
}

void draw_naga(const char* prefix) {
    printf("%s NAGA\n\n", prefix);
    printf("    _ 0_0\n");
    printf("   /_|---'\n");
    printf("   [__]\n");
    printf("  /_/\n");
    printf("  [__]\n");
    printf("  \\__\\\n");
    printf("   [__]\n");
}

void draw_goblin(const char* prefix) {
    printf("%s GOBLIN\n\n", prefix);
    printf("    .-\"-.\n");
    printf("   | o_o |\n");
    printf("  /[#####]\\\n");
    printf("  | [###] |\n");
    printf("   \\_/^\\_/\n");
}


void draw_combat_scene() {
    printf("KNIGHT          GOBLIN\n\n");
    printf("  ---             o_o\n");
    printf(" /   \\           /###\\\n");
    printf("|  0  |          |###|\n");
    printf(" \\V|V/            ^ ^\n");
    printf("  / \\\n\n");
    printf("[===] SWORD     [##] MACE\n\n");
    printf("HP: 75/75       HP: 40/40\n");
}

int main() {
    draw_gryphon("STORM");
    printf("\n-----------------------------------\n\n");
    
    draw_naga("GRANITE");
    printf("\n-----------------------------------\n\n");
    
    draw_goblin("IRON"); 

    printf("\n-----------------------------------\n\n");
    draw_combat_scene();

    return 0;
}
