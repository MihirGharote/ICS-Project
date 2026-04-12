#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void manual_delay(int seconds) {
    clock_t start_time = clock();
   
    while (clock() < start_time + seconds * CLOCKS_PER_SEC);
}

int main() {
    printf(" REACTION TEST (Standard C)\n");
    printf("Press ENTER to start...");
    getchar();

    srand(time(NULL));
   
    int delay_seconds = rand() % 4 + 2;

    printf("\nWaiting...");
    fflush(stdout);

   
    manual_delay(delay_seconds);

    printf("\n--- NOW! ---");
    fflush(stdout);

    clock_t start_reaction = clock();
    
   
    while (getchar() != '\n'); 
    
    clock_t end_reaction = clock();

    double total_time = (double)(end_reaction - start_reaction) / CLOCKS_PER_SEC;

    if (total_time < 0.05) {
        printf("\nToo fast! You likely anticipated the prompt.\n");
    } else {
        printf("\nReaction Time: %.3f seconds\n", total_time);
    }

    return 0;
}
