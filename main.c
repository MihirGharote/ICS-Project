#include <stdio.h>
#include <string.h>
typedef struct game {
    char name[50];
} something;

int main() {
    printf("The game runs!\n");
    something e;
    strcpy(e.name, "PLEASE!!");
    printf("%s", e.name);
    return 0;
}