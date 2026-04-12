#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int num1, num2, choice, answer, userAnswer;
    char op;
    int score = 0;
    clock_t start_t, end_t;
    double total_time;
    srand(time(0));
    printf(" WELCOME TO SPEED ARITHMETIC \n");
    printf("Type -1 to exit\n");
    while (1) {
        num1 = rand() % 20 + 1;
        num2 = rand() % 20 + 1;
        choice = rand() % 3; 
      switch (choice) {
            case 0: op = '+'; answer = num1 + num2; break;
            case 1: op = '-'; answer = num1 - num2; break;
            case 2: op = '*'; answer = num1 * num2; break;
        }
     printf("Solve: %d %c %d = ", num1, op, num2);
        start_t = clock(); 
        if (scanf("%d", &userAnswer) != 1) break;
        end_t = clock(); 
        if (userAnswer == -1) break;
        total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        if (userAnswer == answer) {
            printf("Correct! Time: %.2fs\n", total_time);
         if (total_time < 2.0) {
             score += 10;
         }
            else {
                score += 5;
        }
        }else {
            printf("Wrong! The answer was %d.\n", answer);
            score -= 2;
        }
        printf("Current Score: %d\n\n", score);
    }
    printf(" GAME OVER \n");
    printf("Final Score: %d\n", score);
    return 0;
}
