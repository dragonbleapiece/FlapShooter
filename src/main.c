#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "level.h"

float rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {

  Level level = generateLevelFromFile("ressources/levelOne.ppm");

  printEntityList(level.player);
  printEntityList(level.ennemies);
  printEntityList(level.obstacles);
  printEntityList(level.bonus);
  printEntityList(level.projectiles);

  return EXIT_SUCCESS;
}
