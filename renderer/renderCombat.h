#pragma once
#include "../combat/enemies.h"


void renderCombat(Enemy *enemy);
void renderArt(int init_x, int init_y, char **art, int width, int height);
void renderEnemyAttack(char *message, Enemy *enemy);
void renderPlayerAttack(char *message, Enemy *enemy);