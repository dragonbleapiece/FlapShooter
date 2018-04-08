#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "level.h"

float rand_a_b(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {
  float x = 0;
  float y = 0;
  EntityList lst = NULL;

  for (int i = 0; i < 10; i++) {
    x = rand_a_b(0, 1000);
    y = rand_a_b(0, 50);
    printf("Ajout (%f;%f)\n", x, y);
    addEntityToList(&lst, allocEntity(x, y, rand_a_b(10, 50), rand_a_b(10, 50), (int) rand_a_b(1, 5), (int) rand_a_b(1, 5), (GLuint) rand_a_b(1, 5), NULL));
  }
  printEntityList(lst);
  printf("Remove first \n");
  removeEntityToList(&lst, lst);
  printEntityList(lst);
  printf("Remove all \n");
  freeEntityList(&lst);
  printEntityList(lst);

  return EXIT_SUCCESS;
}